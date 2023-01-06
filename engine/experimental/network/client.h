/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <future>
#include <map>
#include <memory>
#include <string>
#include <thread>

#include <awesome/core/reflection.h>

#include "command_error.h"
#include "connection.h"
#include "message.h"
#include "server_command.h"

namespace net
{
	class Client
	{
	public:

		enum class State
		{
			Closed,
			Connected,
			Initialized,
			Error
		};

		Client() = default;

		void close();
		State connect(const std::string& ip, Address::port_t port);
		void update();

		template <
			typename RequestType, 
			typename ResponseType,
			typename CommandType,
			typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>, 
			typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>,
			typename CommandEnabled = std::enable_if<std::is_base_of<IServerCommand, CommandType>::value>
		>
		std::future<std::tuple<CommandError, ResponseType>> asyncCall(const RequestType& request)
		{
			// if (m_state != State::Connected) return std::future<std::tuple<CommandError, ResponseType>>(std::make_tuple(CommandError::Unknown, ResponseType()));
			
			Message message;
			message.header.commandId = TypeDescriptor::get<CommandType>().name;
			message.body.data = request.serialize();
		
			m_connection->send(m_serverAddress, message);
		
			return	std::async(std::launch::async, [this, messageId = message.header.id]() -> std::tuple<CommandError, ResponseType>
				{
					const std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
					double timeLeft = 0.0;
					
					auto it = m_responseMessages.find(messageId);
					while (it == m_responseMessages.end())
					{
						timeLeft = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count();
						if (timeLeft >= 20.0) // 20 seconds
						{
							return std::make_tuple(CommandError::Timeout, ResponseType());
						}
						it = m_responseMessages.find(messageId);
					}

					const auto& [message, queueTime] = it->second;
					ResponseType response;
					response.deserialize(message.body.data);
					m_responseMessages.erase(it);
					return std::make_tuple(CommandError::OK, response);
				}
			);
		}

		template <
			typename RequestType,
			typename CommandType,
			typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>,
			typename CommandEnabled = std::enable_if<std::is_base_of<IServerCommand, CommandType>::value>
		>
		CommandError call(const RequestType& request)
		{
			if (m_state != State::Connected) return CommandError::Unknown;

			Message message;
			message.header.commandId = TypeDescriptor::get<CommandType>().name;
			message.body.data = request.serialize();

			m_connection->send(m_serverAddress, message);

			return CommandError::OK;
		}

	private:
		std::unique_ptr<Connection> m_connection;
		std::map<netid, std::tuple<Message, std::chrono::high_resolution_clock::time_point>> m_responseMessages;
		Address m_serverAddress;
		State m_state{ State::Initialized };
		std::thread m_updateThread;
	};
}
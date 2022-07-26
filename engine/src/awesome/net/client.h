/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <future>
#include <memory>
#include <string>

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

		// template <
		// 	typename RequestType, 
		// 	typename ResponseType, 
		// 	typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>, 
		// 	typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>
		// >
		// std::future<std::tuple<CommandError, ResponseType>> callAsync(const std::string& commandId, const RequestType& request)
		// {
		// 	if (m_state != State::Connected) return std::make_tuple(CommandError::Unknown, ResponseType());
		// 	
		// 	Message message;
		// 	message.header.commandId = TypeDescriptor::get<CommandType>().name;
		// 	message.body.data = request.serialize()
		// 
		// 	m_connection->send(m_serverAddress, message);
		// 
		// 
		// }

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
		Address m_serverAddress;
		State m_state{ State::Initialized };
	};
}
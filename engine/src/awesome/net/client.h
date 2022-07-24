/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "command_error.h"
#include "connection.h"
#include "message.h"

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

		template <typename RequestType, typename ResponseType, typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>, typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>>
		CommandError call(const std::string& commandId, const RequestType& request, ResponseType& response)
		{
			if (m_state != State::Connected) return CommandError::Unknown;

			return CommandError::Unknown;
		}

		template <typename RequestType, typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>>
		CommandError call(const std::string& commandId, const RequestType& request)
		{
			if (m_state != State::Connected) return CommandError::Unknown;

			Message message;
			message.header.commandId = commandId;
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
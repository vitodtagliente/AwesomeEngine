/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include "client_command.h"
#include "command_error.h"
#include "connection.h"
#include "message.h"
#include "session_manager.h"

namespace net
{
	class Server
	{
	public:

		enum class State
		{
			Closed,
			Initialized,
			Listening,
			Error
		};

		Server() = default;

		void close();
		State listen(Address::port_t port, unsigned int maxConnections);
		void update();

		// template <typename RequestType, typename ResponseType, typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>, typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>>
		// CommandError call(UserSession* const userSession, const std::string& commandId, const RequestType& request, ResponseType& response)
		// {
		// 	if (m_state != State::Listening) return CommandError::Unknown;
		// 
		// 	return CommandError::Unknown;
		// }

		template <
			typename RequestType, 
			typename CommandType, 
			typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>, 
			typename CommandEnabled = std::enable_if<std::is_base_of<IClientCommand, CommandType>::value>
		>
		CommandError call(UserSession* const userSession, const RequestType& request)
		{
			if (m_state != State::Listening) return CommandError::Unknown;

			Message message;
			message.header.commandId = TypeDescriptor::get<CommandType>().name;
			message.body.data = json::Serializer::to_string(request.serialize());

			m_connection->send(userSession->getAddress(), message);

			return CommandError::OK;
		}

	private:
		std::unique_ptr<Connection> m_connection;
		unsigned int m_maxConnections{ 4 };
		SessionManager m_sessionManager;
		State m_state{ State::Initialized };
	};
}
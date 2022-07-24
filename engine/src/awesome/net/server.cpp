#include "server.h"

#include <awesome/core/reflection.h>

#include "server_command.h"

namespace net
{
	void Server::close()
	{
		if (m_state == State::Listening)
		{
			m_connection->close();
			m_state = State::Closed;
		}
	}

	Server::State Server::listen(const Address::port_t port, const unsigned int maxConnections)
	{
		if (m_state == State::Listening) return m_state;

		m_connection = std::make_unique<Connection>();
		Connection::State connectionState = m_connection->connect("127.0.0.1", port);
		if (connectionState == Connection::State::Connected)
		{
			m_maxConnections = maxConnections;
			return m_state = State::Listening, m_state;
		}
		return m_state = State::Error, m_state;
	}

	void Server::update()
	{
		if (m_state != State::Listening) return;

		const auto& packet = m_connection->receive();
		if (packet.has_value())
		{
			auto [address, message] = packet.value();
			UserSession* const userSession = m_sessionManager.findOrAdd(address);

			if (userSession->state == UserSession::State::PendingConnection
				|| userSession->state == UserSession::State::Connected)
			{
				ServerCommandPtr command = std::unique_ptr<IServerCommand>(TypeFactory::instantiate<IServerCommand>(message.header.commandId));
				if (command)
				{
					if (!command->requireAuthentication() || userSession->state == UserSession::State::Connected)
					{
						command->execute(userSession, message);
					}
				}
			}
		}

		// inactivity check
		// TODO

		// send the world update

	}
}
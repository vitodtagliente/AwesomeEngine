#include "server.h"

#include <awesome/core/logger.h>
#include <awesome/core/reflection.h>
#include <awesome/entity/world.h>

#include "server_command.h"

#include "commands/update_world_command.h"

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
			INFO_LOG("Net", THIS_FUNC + " Server listening at port " + std::to_string(port) + "...");
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

			if (userSession->getState() == UserSession::State::PendingConnection
				|| userSession->getState() == UserSession::State::Connected)
			{
				if (message.header.commandPhase == CommandPhase::Request)
				{
					ServerCommandPtr command = std::unique_ptr<IServerCommand>(TypeFactory::instantiate<IServerCommand>(message.header.commandId));
					if (command)
					{
						if (!command->requireAuthentication() || userSession->getState() == UserSession::State::Connected)
						{
							INFO_LOG("Net", THIS_FUNC + " executing the commandId[" + message.header.commandId + "] for the user[" + (std::string)userSession->netId() + "]");
							command->execute(m_connection.get(), userSession, message);
						}
						else
						{
							ERR_LOG("Net", THIS_FUNC + " cannot execute the commandId[" + message.header.commandId + "] for the user[" + (std::string)userSession->netId() + "]. Not authorized.");
						}
					}
					else
					{
						ERR_LOG("Net", THIS_FUNC + " commandId[" + message.header.commandId + "] not found. Unable to process the message for the user[" + (std::string)userSession->netId() + "]");
					}
				}
				else
				{
					// response
				}
			}
		}

		// inactivity check
		m_sessionManager.update();

		// send the world update
		{
			command::UpdateWorldRequest request;
			request.data = World::instance().netSerialize();
			for (UserSession* const userSession : m_sessionManager.getUserSessions())
			{
				if (userSession->getState() == UserSession::State::Connected)
				{
					call<command::UpdateWorldRequest, command::UpdateWorldCommand>(userSession, request);
				}
			}
		}
	}
}
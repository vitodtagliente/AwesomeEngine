#include "server.h"

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
			switch (userSession->state)
			{
			case UserSession::State::PendingConnection:
			{

				break;
			}
			}
		}
	}
}
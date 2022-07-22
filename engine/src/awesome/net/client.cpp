#include "client.h"

#include <awesome/core/reflection.h>

#include "client_command.h"

namespace net
{
	void Client::close()
	{
		if (m_state == State::Connected)
		{
			m_connection->close();
			m_state = State::Closed;
		}
	}

	Client::State Client::connect(const std::string& ip, Address::port_t port)
	{
		if (m_state == State::Connected) return m_state;

		m_connection = std::make_unique<Connection>();
		Connection::State connectionState = m_connection->connect(ip, port);
		if (connectionState == Connection::State::Connected)
		{
			m_serverAddress = Address(ip, port);
			return m_state = State::Connected, m_state;
		}
		return m_state = State::Error, m_state;
	}

	void Client::update()
	{
		if (m_state != State::Connected) return;

		const auto& packet = m_connection->receive();
		if (packet.has_value())
		{
			auto [address, message] = packet.value();
			if (address.getIP() == m_serverAddress.getIP()
				&& address.getPort() == m_serverAddress.getPort())
			{
				ClientCommandPtr command = std::unique_ptr<IClientCommand>(TypeFactory::instantiate<IClientCommand>(message.header.commandId));
				if (command)
				{
					command->execute(message);
				}
			}
		}
	}
}
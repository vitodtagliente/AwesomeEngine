#include "client.h"

#include <vdtproto/runtime.h>

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
		Connection::State connectionState = m_connection->connect(ip, port + 1);
		if (connectionState == Connection::State::Connected)
		{
			m_serverAddress = Address(ip, port);
			m_updateThread = std::thread([this]()
				{
					update();
				}
			);
			m_updateThread.detach();
			return m_state = State::Connected, m_state;
		}
		return m_state = State::Error, m_state;
	}

	void Client::update()
	{
		while (m_state == State::Connected)
		{

			const auto& packet = m_connection->receive();
			if (packet.has_value())
			{
				auto [address, message] = packet.value();
				if (message.header.commandPhase == CommandPhase::Request)
				{
					ClientCommandPtr command = std::unique_ptr<IClientCommand>(TypeFactory::instantiate<IClientCommand>(message.header.commandId));
					if (command)
					{
						command->execute(message);
					}
				}
				else
				{
					m_responseMessages.insert(std::make_pair(message.header.id, std::make_tuple(message, std::chrono::high_resolution_clock::now())));
				}
			}
		}
	}
}
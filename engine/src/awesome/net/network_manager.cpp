#include "network_manager.h"

#include <iostream>

namespace net
{
#define CLIENT_PORT 36000

	bool NetworkManager::connect(const std::string& ip, const uint16_t port)
	{
		m_socket = Socket(net::Address("127.0.0.1", CLIENT_PORT), net::Socket::TransportProtocol::UDP);
		m_type = Type::Client;
		
		if (!m_socket->isValid())
		{
			m_socket = std::nullopt;
			return false;
		}
		return m_socket->connect(net::Address(ip, port));
	}

	bool NetworkManager::listen(const std::string& ip, const uint16_t port, const unsigned int maxConnections)
	{
		m_socket = Socket(net::Address(ip, port), net::Socket::TransportProtocol::UDP);
		m_type = Type::Server;

		if (!m_socket->isValid())
		{
			m_socket = std::nullopt;
			return false;
		}
		return m_socket->listen(maxConnections);
	}

	void NetworkManager::update(const double /*deltaTime*/)
	{
		if (!m_socket.has_value() || !m_socket->isValid())
			return;

		uint8_t buffer[100];
		const std::size_t buffer_size = sizeof(buffer);
		int32_t byteRead{ 0 };
		while (m_socket->receive(buffer, buffer_size, byteRead))
		{
			std::string message{ reinterpret_cast<char*>(buffer), (unsigned int)byteRead };
			std::cout << message << std::endl;
		}
	}
}
#include "network_manager.h"

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

		if (!m_socket->bind())
		{
			return false;
		}

		m_socket->setNonBlockingMode();
		m_serverAddress = net::Address(ip, port);
		return true;
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

		if (!m_socket->bind())
		{
			return false;
		}

		m_socket->setNonBlockingMode();
		return true;
	}

	void NetworkManager::update(const double /*deltaTime*/)
	{
		if (!m_socket.has_value() || !m_socket->isValid()) return;

		uint8_t buffer[100];
		net::Address address;
		const std::size_t buffer_size = sizeof(buffer);
		int32_t byteRead{ 0 };
		while (m_socket->receiveFrom(address, buffer, buffer_size, byteRead))
		{
			std::string data{ reinterpret_cast<char*>(buffer), static_cast<unsigned int>(byteRead) };
			
			Message message;
			message.deserialize(data);

			if (m_type == Type::Server)
			{
				handleMessageServer(address, message);
			}
			else
			{
				handleMessageClient(message);
			}
		}
	}

	void NetworkManager::handleMessageServer(const Address& address, const Message& message)
	{
		Session* session = m_sessionManager.find(address);
		if (session == nullptr)
		{
			// new client connection
			session = m_sessionManager.add(address);
		}


	}

	void NetworkManager::handleMessageClient(const Message& message)
	{
	}
}
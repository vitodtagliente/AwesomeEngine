#include "connection.h"

#include <awesome/encoding/json.h>

namespace net
{
	Connection::State Connection::connect(const std::string& ip, const Address::port_t port)
	{
		m_socket = std::make_unique<Socket>(net::Address(ip, port), net::Socket::TransportProtocol::UDP);
		if (!m_socket->isValid())
		{
			m_socket.release();
			return m_state = State::Error, m_state;
		}

		if (!m_socket->bind())
		{
			m_socket.release();
			return m_state = State::Error, m_state;
		}

		m_socket->setNonBlockingMode();
		return m_state = State::Connected, m_state;
	}

	void Connection::send(const Address& address, const Message& message)
	{
		if (m_state != State::Connected) return;

		int32_t byteSent{ 0 };
		std::string data = json::Serializer::to_string(message.serialize());
		m_socket->sendTo(address, (uint8_t*)data.c_str(), data.size(), byteSent);
	}

	std::optional<std::pair<Address, Message>> Connection::receive()
	{
		if (m_state != State::Connected) return std::nullopt;

		uint8_t buffer[100];
		net::Address address;
		const std::size_t buffer_size = sizeof(buffer);
		int32_t byteRead{ 0 };
		while (m_socket->receiveFrom(address, buffer, buffer_size, byteRead))
		{
			std::string data{ reinterpret_cast<char*>(buffer), static_cast<unsigned int>(byteRead) };

			Message message;
			message.deserialize(data);

			return std::make_pair(address, message);
		}
		return std::nullopt;
	}

	void Connection::close()
	{
		if (m_socket)
		{
			m_socket->close();
			m_state = State::Closed;
		}
	}
}
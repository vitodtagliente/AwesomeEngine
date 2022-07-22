#include "network_manager.h"

namespace net
{
	bool NetworkManager::startClient(const std::string& ip, const Address::port_t port)
	{
		return false;
	}

	bool NetworkManager::startServer(const Address::port_t port, const unsigned int maxConnections)
	{
		if (m_type != Type::Unknown) return false;

		m_type = Type::Server;
		m_server = std::make_unique<Server>();
		return m_server->listen(port, maxConnections) == Server::State::Listening;
	}

	void NetworkManager::update(const double /*deltaTime*/)
	{
		if (m_type == Type::Server)
		{
			m_server->update();
		}
		else if (m_type == Type::Client)
		{

		}
	}
}
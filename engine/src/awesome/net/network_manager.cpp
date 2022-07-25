#include "network_manager.h"

#include "server_commands/hello_command.h"

namespace net
{
	bool NetworkManager::startClient(const std::string& ip, const Address::port_t port)
	{
		if (m_type != Type::Offline) return false;

		m_type = Type::Client;
		m_client = std::make_unique<Client>();
		if (m_client->connect(ip, port) == Client::State::Connected)
		{
			Hello request;
			request.text = "Hello Server";
			m_client->call("HelloCommand", request);
			return true;
		}
		return false;
	}

	bool NetworkManager::startServer(const Address::port_t port, const unsigned int maxConnections)
	{
		if (m_type != Type::Offline) return false;

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
			m_client->update();
		}
	}

	bool NetworkManager::hasNetworkAuthority() const
	{
		return m_type == Type::Offline || m_type == Type::Server;
	}

	bool NetworkManager::hasNetworkAuthority(const NetMode netMode) const
	{
		if (netMode == NetMode::Client && m_type == Type::Server) return false;
		if (netMode == NetMode::Server && m_type == Type::Client) return false;
		return true;
	}
}
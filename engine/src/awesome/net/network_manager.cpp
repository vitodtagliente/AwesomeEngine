#include "network_manager.h"

#include "server_commands/hello_command.h"

namespace net
{
	bool NetworkManager::startClient(const std::string& ip, const Address::port_t port)
	{
		if (m_state != State::Offline) return false;

		m_state = State::Client;
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
		if (m_state != State::Offline) return false;

		m_state = State::Server;
		m_server = std::make_unique<Server>();
		return m_server->listen(port, maxConnections) == Server::State::Listening;
	}

	void NetworkManager::update(const double /*deltaTime*/)
	{
		if (m_state == State::Server)
		{
			m_server->update();
		}
		else if (m_state == State::Client)
		{
			m_client->update();
		}
	}

	bool NetworkManager::hasNetworkAuthority() const
	{
		return m_state == State::Offline || m_state == State::Server;
	}

	bool NetworkManager::hasNetworkAuthority(const NetMode netMode) const
	{
		if (netMode == NetMode::Client && m_state == State::Server) return false;
		if (netMode == NetMode::Server && m_state == State::Client) return false;
		return true;
	}
	
	bool NetworkManager::isOnline() const
	{
		return m_state != State::Offline;
	}
}
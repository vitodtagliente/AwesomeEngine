#include "network_manager.h"

namespace net
{
	bool NetworkManager::startClient(const std::string& ip, const Address::port_t port)
	{
		if (m_state != State::Offline) return false;

		m_state = State::Client;
		m_client = std::make_unique<Client>();
		if (m_client->connect(ip, port) == Client::State::Connected)
		{
			// command::ConnectRequest request;
			// auto commandResult = m_client->asyncCall<command::ConnectRequest, command::ConnectResponse, command::ConnectCommand>(request);
			// // commandResult.wait();
			// const auto& [commandError, response] = commandResult.get();
			// if (commandError == CommandError::OK)
			// {
			// 	return true;
			// }
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
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <string>

#include <awesome/core/singleton.h>

#include "client.h"
#include "net_mode.h"
#include "server.h"

namespace net
{
	class NetworkManager : public Singleton<NetworkManager>
	{
	public:

		enum class State
		{
			Offline,
			Client,
			Server
		};

		bool startClient(const std::string& ip, Address::port_t port);
		bool startServer(Address::port_t port, unsigned int maxConnections);

		void update(double deltaTime);

		inline State getState() const { return m_state; }

		bool hasNetworkAuthority() const;
		bool hasNetworkAuthority(NetMode netMode) const;
		bool isOnline() const;

	private:
		std::unique_ptr<Client> m_client;
		std::unique_ptr<Server> m_server;
		std::optional<net::Address> m_serverAddress;
		State m_state{ State::Offline };
	};
}
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <string>

#include <awesome/core/singleton.h>

#include "client.h"
#include "server.h"

namespace net
{
	class NetworkManager : public Singleton<NetworkManager>
	{
	public:

		enum class Type
		{
			Unknown,
			Client,
			Server
		};

		NetworkManager() = default;

		bool startClient(const std::string& ip, Address::port_t port);
		bool startServer(Address::port_t port, unsigned int maxConnections);

		void update(double deltaTime);

		inline Type getType() const { return m_type; }

	private:
		std::unique_ptr<Client> m_client;
		std::unique_ptr<Server> m_server;
		std::optional<net::Address> m_serverAddress;
		Type m_type{ Type::Unknown };
	};
}
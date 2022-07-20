/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <string>

#include <awesome/core/singleton.h>

#include <vdtnet/socket.h>

#include "session_manager.h"

namespace net
{
	class NetworkManager : public Singleton<NetworkManager>
	{
	public:

		enum class Type
		{
			Client,
			Server
		};

		NetworkManager() = default;

		bool connect(const std::string& ip, uint16_t port);
		bool listen(const std::string& ip, uint16_t port, unsigned int maxConnections);

		void update(double deltaTime);

		inline Type getType() const { return m_type; }

	private:
		SessionManager m_sessionManager;
		std::optional<net::Address> m_serverAddress;
		std::optional<Socket> m_socket;
		Type m_type;
	};
}
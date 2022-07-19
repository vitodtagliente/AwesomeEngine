/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <string>

#include <awesome/core/singleton.h>

#include <vdtnet/socket.h>

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

	private:
		std::optional<Socket> m_socket;
		Type m_type;
	};
}
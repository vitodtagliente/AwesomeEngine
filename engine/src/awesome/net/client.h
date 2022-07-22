/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "connection.h"
#include "message.h"

namespace net
{
	class Client
	{
	public:

		enum class State
		{
			Closed,
			Connected,
			Initialized,
			Error
		};

		Client() = default;

		void close();
		State connect(const std::string& ip, Address::port_t port);
		void update();

	private:
		std::unique_ptr<Connection> m_connection;
		Address m_serverAddress;
		State m_state{ State::Initialized };
	};
}
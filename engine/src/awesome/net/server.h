/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include "connection.h"
#include "message.h"
#include "session_manager.h"

namespace net
{
	class Server
	{
	public:

		enum class State
		{
			Closed,
			Initialized,
			Listening,
			Error
		};

		Server() = default;

		void close();
		State listen(Address::port_t port, unsigned int maxConnections);
		void update();

	private:
		std::unique_ptr<Connection> m_connection;
		unsigned int m_maxConnections;
		SessionManager m_sessionManager;
		State m_state{ State::Initialized };
	};
}
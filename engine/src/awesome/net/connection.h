/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <optional>

#include <vdtnet/socket.h>

#include "message.h"

namespace net
{
	class Connection
	{
	public:

		enum class State
		{
			Connected,
			Closed,
			Error,
			Initialized
		};

		Connection() = default;
		virtual ~Connection() = default;

		State getState() const { return m_state; }

		void close();
		State connect(const std::string& ip, const Address::port_t port);
		void send(const Address& address, const Message& message);
		std::optional<std::pair<Address, Message>> receive();

	protected:
		std::unique_ptr<Socket> m_socket;
		State m_state{ State::Initialized };
	};
}
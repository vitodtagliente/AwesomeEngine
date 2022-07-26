/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <memory>

#include <vdtnet/address.h>

#include "net_id.h"

namespace net
{
	class UserSession
	{
	public:
		
		enum class State
		{
			Connected,
			Disconnected,
			PendingConnection,
			PendingDisconnection,
		};

		UserSession(const Address& address);

		inline const netid& netId() const { return m_id; }
		inline const Address& getAddress() const { return m_address; }
		inline const State getState() const { return m_state; }

		void connect();
		void disconnect();
		void resetInactivityTime();
		double getInactivityTime() const;

	private:
		Address m_address;
		netid m_id;
		std::chrono::high_resolution_clock::time_point m_inactivityTime;
		State m_state{ State::PendingConnection };
	};

	typedef std::unique_ptr<UserSession> UserSessionPtr;
}
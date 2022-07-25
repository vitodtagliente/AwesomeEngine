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

		const Address& getAddress() const { return m_address; }
		const netid& netId() const { return m_id; }

		void resetInactivityTime();
		double getInactivityTime() const;

		State state{ State::PendingConnection };

	private:
		Address m_address;
		netid m_id;
		std::chrono::high_resolution_clock::time_point m_inactivityTime;
	};

	typedef std::unique_ptr<UserSession> UserSessionPtr;
}
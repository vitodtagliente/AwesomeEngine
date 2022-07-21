/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <memory>

#include "netid.h"

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

		UserSession() = default;

		const netid& netId() const { return m_id; }

		void resetInactivityTime();
		double getInactivityTime() const;

		State state{ State::PendingConnection };

	private:
		netid m_id;
		std::chrono::high_resolution_clock::time_point m_inactivityTime{ std::chrono::high_resolution_clock::now() };
	};

	typedef std::unique_ptr<UserSession> UserSessionPtr;
}
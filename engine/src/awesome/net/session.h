/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <memory>

#include "netid.h"

namespace net
{
	class Session
	{
	public:
		
		enum class State
		{
			PendingConnection,
			Connected,
			PendingDisconnection,
			Disconnected
		};

		Session() = default;

		const netid& netId() const { return m_id; }

		void resetInactivityTime();
		double getInactivityTime() const;

	private:
		netid m_id;
		std::chrono::high_resolution_clock::time_point m_inactivityTime{ std::chrono::high_resolution_clock::now() };
	};

	typedef std::unique_ptr<Session> SessionPtr;
}
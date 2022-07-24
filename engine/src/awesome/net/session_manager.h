/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <vector>

#include <vdtnet/address.h>

#include "user_session.h"

namespace net
{
	class SessionManager
	{
	public:
		SessionManager() = default;

		UserSession* const add(const Address& address);
		UserSession* const find(const Address& address, bool resetInactivityTime) const;
		UserSession* const findOrAdd(const Address& address);
		void remove(const Address& address);

		std::vector<UserSession*> getUserSessions() const;

	private:
		std::map<Address, UserSessionPtr> m_sessions;
	};
}
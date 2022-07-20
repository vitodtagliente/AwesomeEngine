/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>

#include <vdtnet/address.h>

#include "session.h"

namespace net
{
	class SessionManager
	{
	public:
		SessionManager() = default;

		Session* const add(const Address& address);
		Session* const find(const Address& address) const;
		void remove(const Address& address);

	private:
		std::map<Address, SessionPtr> m_sessions;
	};
}
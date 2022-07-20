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



	private:
		std::map<Address, Session> m_sessions;
	};
}
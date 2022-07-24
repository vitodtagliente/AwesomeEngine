#include "session_manager.h"

namespace net
{
	UserSession* const SessionManager::add(const Address& address)
	{
		auto newPair = m_sessions.insert(std::make_pair(address, std::make_unique<UserSession>(address)));
		return newPair.first->second.get();
	}

	UserSession* const SessionManager::find(const Address& address, const bool resetInactivityTime) const
	{
		const auto& it = m_sessions.find(address);
		if (it != m_sessions.end())
		{
			if (resetInactivityTime)
			{
				it->second->resetInactivityTime();
			}
			return it->second.get();
		}
		return nullptr;
	}

	UserSession* const SessionManager::findOrAdd(const Address& address)
	{
		const auto& it = m_sessions.find(address);
		if (it != m_sessions.end())
		{
			it->second->resetInactivityTime();
			return it->second.get();
		}

		return add(address);
	}

	void SessionManager::remove(const Address& address)
	{
		m_sessions.erase(address);
	}
}
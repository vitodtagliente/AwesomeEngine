#include "session_manager.h"

namespace net
{
	Session* const SessionManager::add(const Address& address)
	{
		auto newPair = m_sessions.insert(std::make_pair(address, std::make_unique<Session>()));
		return newPair.first->second.get();
	}

	Session* const SessionManager::find(const Address& address) const
	{
		const auto& it = m_sessions.find(address);
		if (it != m_sessions.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

	void SessionManager::remove(const Address& address)
	{
		m_sessions.erase(address);
	}
}
#include "session_manager.h"

#include <queue>
#include <string>

#include <awesome/core/logger.h>

namespace net
{
	UserSession* const SessionManager::add(const Address& address)
	{
		auto newPair = m_sessions.insert(std::make_pair(address, std::make_unique<UserSession>(address)));
		UserSession* const userSession = newPair.first->second.get();

		INFO_LOG("Net", THIS_FUNC + " Accepted a new session[" + (std::string)userSession->netId() + "]");
		return userSession;
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

	void SessionManager::update()
	{
		std::queue<Address> sessionsToRemove;
		for (const auto& pair : m_sessions)
		{
			UserSession* const userSession = pair.second.get();
			if (userSession->getState() == UserSession::State::PendingDisconnection
				|| userSession->getInactivityTime() > 20.0) // 20 seconds
			{
				INFO_LOG("Net", THIS_FUNC + " Closing the session[" + (std::string)userSession->netId() + "]");
				sessionsToRemove.push(pair.first);
			}
		}

		while (!sessionsToRemove.empty())
		{
			const Address address = sessionsToRemove.front();
			m_sessions.erase(address);
			sessionsToRemove.pop();
		}
	}

	std::vector<UserSession*> SessionManager::getUserSessions() const
	{
		std::vector<UserSession*> result;
		for (const auto& pair : m_sessions)
		{
			result.push_back(pair.second.get());
		}
		return result;
	}
}
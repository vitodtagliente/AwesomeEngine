#include "user_session.h"

namespace net
{
	void UserSession::resetInactivityTime()
	{
		m_inactivityTime = std::chrono::high_resolution_clock::now();
	}

	double UserSession::getInactivityTime() const
	{
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_inactivityTime).count();
	}
}
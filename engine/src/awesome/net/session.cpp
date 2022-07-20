#include "session.h"

namespace net
{
	void Session::resetInactivityTime()
	{
		m_inactivityTime = std::chrono::high_resolution_clock::now();
	}

	double Session::getInactivityTime() const
	{
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_inactivityTime).count();
	}
}
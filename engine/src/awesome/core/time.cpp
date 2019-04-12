#include "time.h"

namespace awesome
{
	Time::Time()
		: m_time(0.0)
		, m_deltaTime(0.0)
	{
	}

	Time::~Time()
	{
	}

	void Time::tick()
	{
		// update time data
		const double last_time = m_time;
		m_time = platformGetTime();
		m_deltaTime = m_time - last_time;
	}
}
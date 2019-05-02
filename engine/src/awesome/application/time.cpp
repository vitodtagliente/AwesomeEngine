#include "time.h"

#include "../data/timer.h"

namespace awesome
{
	Time::Time()
		: m_time(0.0),
		m_deltaTime(0.0)
	{

	}

	Time::~Time()
	{

	}

	void Time::update()
	{
		// update time data
		const double last_time = m_time;
		m_time = getApplicationTime();
		m_deltaTime = m_time - last_time;

		// update all the timers
		Timer::update(m_deltaTime);
	}
}
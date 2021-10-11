#include "timer.h"

Timer::Timer(double time)
	: m_time(time)
	, m_timer(time)
	, m_canTick(true)
{
}

void Timer::tick(double deltaTime)
{
	if (m_timer > 0 && m_canTick)
	{
		m_timer -= deltaTime;
	}
}

void Timer::reset()
{
	m_timer = m_time;
}

void Timer::pause()
{
	m_canTick = false;
}

void Timer::resume()
{
	m_canTick = true;
}

void Timer::stop()
{
	m_timer = m_time;
	m_canTick = false;
}

void Timer::configure(double time)
{
	m_timer = m_time = time;
}
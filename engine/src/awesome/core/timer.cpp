#include "timer.h"

namespace awesome
{
	Timer::Timer(const double t_duration, const bool t_loop)
		: m_duration(t_duration)
		, m_time(t_duration)
		, m_loop(t_loop)
		, m_callback()
	{
	}

	Timer::Timer(const double t_duration, const std::function<void()>& t_callback, const bool t_loop)
		: m_duration(t_duration)
		, m_time(t_duration)
		, m_loop(t_loop)
		, m_callback(t_callback)
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::start()
	{
		m_time = m_duration;
		m_isTicking = true;
	}

	void Timer::stop()
	{
		m_isTicking = false;
	}

	void Timer::tick(const double t_deltaTime)
	{
		if (m_isTicking)
		{
			m_time -= t_deltaTime;
			if (m_time <= 0.0)
			{
				m_callback();
				onTimeElapsed.broadcast();

				if (m_loop)
				{
					start();
				}
				else
				{
					stop();
				}
			}
		}
	}
}
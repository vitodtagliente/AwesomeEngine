#include "timer.h"

namespace awesome
{
	std::vector<Timer*> Timer::m_instances {};

	Timer::Timer(const double t_duration, const bool t_loop)
		: m_duration(t_duration)
		, m_time(t_duration)
		, m_loop(t_loop)
	{
		// store the pointer to this instance
		m_instances.push_back(this);
	}

	Timer::Timer(const double t_duration, const std::function<void()>& t_callback, const bool t_loop)
		: m_duration(t_duration)
		, m_time(t_duration)
		, m_loop(t_loop)
	{
		m_instances.push_back(this);
		// set this callback
		onTimeElapsed.addListener(t_callback);
	}

	Timer::~Timer()
	{
		// this timer is going to be destroyed
		for (auto it = m_instances.begin(); it != m_instances.end(); ++it)
		{
			if (*it == this)
			{
				m_instances.erase(it);
				break;
			}
		}
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

	void Timer::update(const double t_deltaTime)
	{
		for (Timer* timer : m_instances)
		{
			timer->tick(t_deltaTime);
		}
	}
}
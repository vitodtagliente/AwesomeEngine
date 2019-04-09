#include <awesome/core/timer.h>

namespace awesome
{
	// store timer instances here
	std::vector<Timer*> Timer::m_Instances{};

	Timer::Timer(const double duration, const bool can_loop /*= false*/) {
		m_Duration = duration;
		loop = can_loop;
		// store this instance
		m_Instances.push_back(this);
	}

	Timer::Timer(const double duration, const std::function<void()>& callback, const bool can_loop /*= false*/) {
		m_Duration = duration;
		loop = can_loop;
		// store this instance
		m_Instances.push_back(this);
		// set the callback
		onTimeElapsed.addListener(callback);
	}

	Timer::~Timer() {
		// this timer is going to be destroyed 
		// erase this instance
		for (auto it = m_Instances.begin(); it != m_Instances.end(); ++it) {
			if (*it == this) {
				m_Instances.erase(it);
				break;
			}
		}
	}

	void Timer::tick(const double delta_time) {
		if (m_IsTicking) {
			m_TimeCounter -= delta_time;
			if (m_TimeCounter <= 0.0)
			{
				onTimeElapsed.broadcast();

				if (loop) 
					start();
				else stop();
			}				
		}
	}

	void Timer::start() {
		m_IsTicking = true;
		m_TimeCounter = m_Duration;
	}

	void Timer::stop() {
		m_IsTicking = false;
		m_TimeCounter = m_Duration;
	}

	void Timer::reset() {
		m_TimeCounter = m_Duration;
	}
}
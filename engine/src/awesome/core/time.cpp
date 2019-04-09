#include <awesome/core/time.h>
#include <awesome/core/timer.h>

namespace awesome
{
	Time* Time::m_Instance = nullptr;

	Time* Time::instance() {
		if (m_Instance == nullptr)
			m_Instance = new Time();
		return m_Instance;
	}

	Time& Time::get() {
		return *instance();
	}

	void Time::free()
	{
		delete m_Instance;
	}

	void Time::tick() {
		// compute the delta time
		const auto last_time = m_Time;
		platformTick();
		m_DeltaTime = m_Time - last_time;

		// update timers
		for (auto& m_instance : Timer::m_Instances)
		{
			if (m_instance)
			{
				m_instance->tick(m_DeltaTime);
			}
		}
	}
}
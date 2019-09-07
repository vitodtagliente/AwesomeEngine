#pragma once

#include <chrono>
#include "singleton.h"

namespace awesome
{
	class Time : public Singleton<Time>
	{
	public:

		// only the engine can let the time to tick
		friend class Engine;

		Time();

		// retrieve the time data
		inline double getTime() const { return m_time; }
		inline double getDeltaTime() const { return m_deltaTime; }


	private:

		// tick the time
		void tick();

		// high resolution clocks
		std::chrono::high_resolution_clock::time_point m_clock1;
		std::chrono::high_resolution_clock::time_point m_clock2;

		// cache time and delta time
		double m_time;
		double m_deltaTime;
	};
}
#pragma once

#include <vector>
#include "event.h"

/*
Engine Timer object implementation
*/

namespace awesome
{
	class Timer final
	{
	private:

		// how much the timers should tick
		double m_duration{ 0.0 };
		// time counter
		double m_timeCounter{ 0.0 };
		// is the timer ticking? or is it in pause?
		bool m_isTicking{ false };

		friend class Time;
		// store all timers instances
		static std::vector<Timer*> m_instances;
		// called by Time's tick
		void tick(const double delta_time);

	public:

		// should the timer loop
		bool loop{ false };

		// event 
		Event onTimeElapsed;

		Timer(const double duration, const bool can_loop = false);
		Timer(const double duration, const std::function<void()>& callback, const bool can_loop = false);
		~Timer();

		Timer& operator=(Timer&& timer) = delete;
		Timer(const Timer& timer) = delete;
		Timer(Timer&& timer) = delete;
		Timer& operator= (const Timer& timer) = delete;

		// timer management functions
		void start();
		inline void pause() { m_isTicking = false; }
		inline void resume() { m_isTicking = true; }
		void stop();
		void reset();

		// set the timer duration
		// this will lost timer progression
		inline void setDuration(const double duration) { m_timeCounter = m_duration = duration; }

		// is the timer ticking? or no?
		inline bool isTicking() const { return m_isTicking; }

		// is the timer elapsed?
		inline bool isElapsed() const { return m_timeCounter <= 0.0; }
	};
}
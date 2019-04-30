#pragma once

#include <functional>
#include <vector>
#include "event.h"

namespace awesome
{
	class Timer final
	{
	public:

		friend class Time;

		Timer(const double t_duration, const bool t_loop = false);
		Timer(const double t_duration, const std::function<void()>& t_callback, const bool t_loop = false);
		~Timer();

		Timer& operator=(Timer&& t_timer) = delete;
		Timer(const Timer& t_timer) = delete;
		Timer(Timer&& t_timer) = delete;
		Timer& operator= (const Timer& t_timer) = delete;

		// timer management functions
		void start();
		inline void pause() { m_isTicking = false; }
		inline void resume() { m_isTicking = true; }
		void stop();

		// is the timer ticking?
		inline bool isTicking() const { return m_isTicking; }
		// is the timer elapsed?
		inline bool isElapsed() const { return m_time <= 0.0; }

		// events
		Event onTimeElapsed;

	private:

		// update this timer
		void tick(const double t_deltaTime);
		// update all timer instances, called by Time
		static void update(const double t_deltaTime);

		// how much the timer should tick
		double m_duration;
		// time counter
		double m_time;
		// true if the timer can loop
		bool m_loop;
		// is the timer ticking?
		bool m_isTicking;

		// all timer instances
		static std::vector<Timer*> m_instances;
	};
}
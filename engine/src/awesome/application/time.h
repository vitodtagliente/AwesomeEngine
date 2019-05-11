#pragma once

#include "../core/singleton.h"

namespace awesome
{
	class Time : public Singleton<Time>
	{
	public:
			   
		Time();
		
		// retrieve the time data
		inline double getTime() const { return m_time; }
		inline double getDeltaTime() const { return m_deltaTime; }

		// initialize
		void initialize();
		// tick the time
		void tick();

	protected:
		
		// get the current time
		virtual double getTime_implementation() const = 0;

		// cache time and delta time
		double m_time;
		double m_deltaTime;
	};
}
#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Time : public Module<Time>
	{
	public:
			   
		Time();
		virtual ~Time() override;

		Time& operator=(Time&& t_time) = delete;
		Time(const Time& t_time) = delete;
		Time(Time&& t_time) = delete;
		Time& operator= (const Time& t_time) = delete;

		// application module interface
		virtual void update() override;

		// retrieve the time data
		inline double getTime() const { return m_time; }
		inline double getDeltaTime() const { return m_deltaTime; }

	protected:
		
		// return the current application's time
		// platform specific implementation
		virtual double getApplicationTime() const = 0;

		// cache time and delta time
		double m_time;
		double m_deltaTime;
	};
}
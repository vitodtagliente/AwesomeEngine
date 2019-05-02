#pragma once

#include "../core/singleton.h"

namespace awesome
{
	class Time : public Singleton<Time>
	{
	public:

		friend class Application;

		Time();
		virtual ~Time() override;

		Time& operator=(Time&& t_time) = delete;
		Time(const Time& t_time) = delete;
		Time(Time&& t_time) = delete;
		Time& operator= (const Time& t_time) = delete;

		// retrieve the time data
		inline double getTime() const { return m_time; }
		inline double getDeltaTime() const { return m_deltaTime; }

	protected:
		
		// return the current application's time
		// platform specific implementation'
		virtual double getApplicationTime() const = 0;

		// cache time and delta time
		double m_time;
		double m_deltaTime;

	private:

		// called by the application
		void update();

	};
}
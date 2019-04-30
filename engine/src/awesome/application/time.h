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

		// retrieve the time data
		inline double getTime() const { return m_time; }
		inline double getDeltaTime() const { return m_deltaTime; }

	protected:

		// cache time and delta time
		double m_time;
		double m_deltaTime;

	};
}
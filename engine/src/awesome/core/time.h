#pragma once

/*
	The Time class manages the engine time.
	It is responsible for generating the delta time used by the engine and its objects.
*/

namespace awesome
{
	class Time final
	{
	public:

		friend class Engine;

		Time();
		~Time();

		Time& operator=(Time&& t_time) = default;
		Time(const Time& t_time) = default;
		Time(Time&& t_time) = default;
		Time& operator= (const Time& t_time) = default;

		// retrieve the time data
		inline double getTime() const { return m_time; }
		inline double getDeltaTime() const { return m_deltaTime; }

	private:

		// called by the engine loop
		void tick();
		// platform specific impementation
		// m_time is updated here
		double platformGetTime() const;

		// cache time and delta time
		double m_time;
		double m_deltaTime;
	};
}
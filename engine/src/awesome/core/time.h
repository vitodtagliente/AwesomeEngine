#pragma once

/*
The Time class manages the application time.
It is responsible for generating the delta time used by components logic and the application time.
It's tick method should be called from the application, inside the main loop.
*/

namespace awesome
{
	class Time final
	{
	private:
		// singleton pattern
		static Time* m_Instance;

		// private constructor and destructor by singleton pattern
		Time() = default;
		~Time() = default;

		// cache time and delta time
		double m_Time{ 0.0 };
		double m_DeltaTime{ 0.0 };

		// is the time ticking? or is it in pause?
		bool m_IsTicking{ true };

		friend class Application;
		// called by application loop cycle
		void tick();
		// platform specific implementation: update m_Time here
		void platformTick();

	public:

		// singleton pattern
		static Time* instance();
		static Time& get(); 

		// destroy the time instance
		static void free();

		Time& operator=(Time&& time) = default;
		Time(const Time& time) = default;
		Time(Time&& time) = default;
		Time& operator= (const Time& time) = default;

		// retrieve the time data
		inline double getTime() const { return m_Time; };
		inline double getDeltaTime() const { return m_DeltaTime; }
		
		// time can be paused and resumed
		inline void pause() { m_IsTicking = false; }
		inline void resume() { m_IsTicking = true; }

		// is the time ticking? or no?
		inline bool isTicking() const { return m_IsTicking; }

		// quick static access functions
		inline static double time() { return instance()->getTime(); }
		inline static double deltaTime() { return instance()->getDeltaTime(); }
	};
}
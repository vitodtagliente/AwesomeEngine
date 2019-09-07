#pragma once

#include <awesome/core/singleton.h>

namespace awesome
{
	class ApplicationAPI;
	class Time;
	class Window;


	class Application : public Singleton<Application>
	{
	public:
		
		Application(ApplicationAPI * const t_api);
		virtual ~Application();

		virtual bool initialize();
		virtual void update();
		virtual void close();

		const Time* const getTime() const { return m_time; }
		const Window* const getWindow() const { return m_window; }

	protected:

		// api 
		ApplicationAPI* m_api;
		// time 
		Time* m_time;
		// window
		Window* m_window;
	};
}
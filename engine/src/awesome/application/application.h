#pragma once

#include <awesome/core/singleton.h>

namespace awesome
{
	class ApplicationAPI;
	class Window;

	class Application : public Singleton<Application>
	{
	public:
		
		Application(ApplicationAPI * const t_api);
		virtual ~Application();

		virtual bool initialize();
		virtual void update();
		virtual void close();

		const Window* const getWindow() const { return m_window; }

	protected:

		// api 
		ApplicationAPI* m_api;
		// window
		Window* m_window;
	};
}
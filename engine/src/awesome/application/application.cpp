#include "application.h"

#include <cassert>
#include "../engine/engine.h"
#include "window.h"

namespace awesome
{
	Application::Application()
		: m_isRunning(false)
	{
	}

	bool Application::startup_implementation()
	{
		if (Engine* const engine = Engine::instance())
		{
			registerModules(engine);

			m_isRunning = true;
			return true;
		}
		return false;		
	}

	void Application::update_implementation()
	{
		// #todo: now the application is running until
		// its window is open
		m_isRunning = Window::instance()->isOpen();
	}
}
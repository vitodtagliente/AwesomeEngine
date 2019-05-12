#include "application_module.h"

#include <cassert>

#include "application.h"
#include "input.h"
#include "time.h"
#include "window.h"

namespace awesome
{
	ApplicationModule::ApplicationModule()
		: m_application()
		, m_input()
		, m_time()
		, m_window()
	{
	}

	ApplicationModule::~ApplicationModule()
	{
		delete m_application;
		delete m_time;
		delete m_input;
		delete m_window;
	}

	bool ApplicationModule::startup_implementation()
	{
		if (initialize())
		{
			assert(m_application && m_input && m_time && m_window);
			// setup the application
			m_application->initialize();
			// setup the window
			// #todo: now are default settings
			Window::Settings window_settings{};
			if (m_window->open(window_settings))
			{
				return m_input->initialize(m_window);
			}
		}		
		return false;
	}

	void ApplicationModule::shutdown_implementation()
	{
		m_window->close();
	}

	void ApplicationModule::update_implementation()
	{
		if (m_window->isOpen())
		{
			// update the time
			m_time->tick();

			// update the application and its core components
			m_application->update();
			m_window->update();
			m_input->update();
		}
	}
}

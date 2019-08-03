#include "application.h"

#include "application_api.h"
#include "input.h"
#include "time.h"
#include "window.h"

namespace awesome
{
	Application::Application(ApplicationAPI* const t_api)
		: m_api(t_api)
		, m_input()
		, m_time()
		, m_window()
	{
	}

	Application::~Application()
	{
		delete m_input;
		delete m_time;
		delete m_window;
	}

	bool Application::initialize()
	{
		m_input = m_api->createInput();
		m_time = m_api->createTime();
		m_window = m_api->createWindow();

		if (m_input && m_time && m_window)
		{
			// #todo: now are default settings
			Window::Settings window_settings{};
			if (m_window->open(window_settings))
			{
				return m_input->initialize(m_window);
			}
		}
		return false;
	}

	void Application::update()
	{
		m_time->tick();
		m_window->update();
		m_input->update();
	}

	void Application::close()
	{
		m_window->close();
	}
}
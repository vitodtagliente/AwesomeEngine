#include "application.h"

#include "application_api.h"
#include "window.h"

namespace awesome
{
	Application::Application(ApplicationAPI* const t_api)
		: m_api(t_api)
		, m_window()
	{
	}

	Application::~Application()
	{
		delete m_window;
	}

	bool Application::initialize()
	{
		m_window = m_api->createWindow();

		if (m_window)
		{
			// #todo: now are default settings
			Window::Settings window_settings{};
			return m_window->open(window_settings);
		}
		return false;
	}

	void Application::update()
	{
		m_window->update();
	}

	void Application::close()
	{
		m_window->close();
	}
}
#include "application.h"

#include "window.h"

namespace awesome
{
	Application::Application(const ApplicationModule::API& t_api)
		: m_api(t_api)
		, m_window()
	{
	}

	Application::~Application()
	{

	}

	bool Application::initialize()
	{
		m_window = std::move(m_api.make_window());
		assert(m_window);
		// #todo: now are default settings
		Window::Settings window_settings{};
		return m_window->open(window_settings);
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
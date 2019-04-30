#include "application.h"

#include "time.h"
#include "window.h"

namespace awesome
{
	Application::Application()
		: m_input(nullptr),
		m_time(nullptr),
		m_window(nullptr)
	{
	}

	Application::~Application()
	{
		delete m_input;
		delete m_window;
		delete m_time;
	}

	bool Application::startup()
	{
		return true;
	}

	void Application::shutdown()
	{
	}

	void Application::tick(const double t_deltaTime)
	{

	}

	Window* Application::getWindow() const
	{
		return m_window;
	}
}
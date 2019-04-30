#include "application.h"

#include "window.h"

namespace awesome
{
	Application::Application()
		: m_window(nullptr)
	{
	}

	Application::~Application()
	{
	}

	bool Application::startup()
	{
		return true;
	}

	void Application::shutdown()
	{
	}

	Window* Application::getWindow() const
	{
		return m_window;
	}
}
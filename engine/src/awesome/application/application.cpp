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

	Window* Application::getWindow() const
	{
		return m_window;
	}
}
#include "window.h"

namespace awesome
{
	// default configuration
	Window::Settings::Settings()
		: title("Awesome")
		, width(640)
		, height(480)
		, fullscreen(false)
		, vsync(false)
	{

	}

	Window::Window()
		: m_isOpen(false)
	{
	}

	bool Window::startup_implementation()
	{
		// #todo: get default app size by config
		Settings window_settings{};
		// open the window
		m_isOpen = open(window_settings);
		return m_isOpen;
	}

	void Window::close()
	{
		if (m_isOpen)
		{
			close_implementation();
			m_isOpen = false;
		}
	}
}
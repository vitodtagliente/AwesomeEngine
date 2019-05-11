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

	bool Window::open(const Settings& t_settings)
	{
		m_isOpen = open_implementation(t_settings);
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

	void Window::update()
	{
		if (m_isOpen)
		{
			update_implementation();
		}
	}
}
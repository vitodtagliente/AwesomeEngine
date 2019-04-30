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
		: m_state(State::Unknown)
	{

	}

	Window::~Window()
	{

	}

	Window::State Window::getState() const
	{
		return m_state;
	}

	void Window::close()
	{
		if (m_state == State::Open)
		{
			m_state = State::Closing;
		}
	}
}
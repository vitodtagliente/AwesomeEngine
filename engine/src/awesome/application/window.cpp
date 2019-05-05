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

	bool Window::startup_implementation()
	{
		// #todo: get default app size by config
		Settings window_settings{};
		// open the window
		const bool success = open(window_settings);
		m_state = success ? State::Open : State::Error;
		return success;
	}

	bool Window::close()
	{
		if (m_state == State::Open || m_state == State::PendingClose)
		{
			m_state = State::Closing;
			const bool success = close_implementation();
			m_state = success ? State::Closed : State::Open;
			return success;
		}
		return false;
	}
}
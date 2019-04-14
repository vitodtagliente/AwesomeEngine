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
		, m_windowHandler(nullptr)
	{

	}

	Window::~Window()
	{

	}

	bool Window::open(const Settings& t_settings)
	{
		if (m_state != State::Created)
		{
			const bool successful = platformOpen(t_settings);
			m_state = successful ? State::Open : State::Error;
			return successful;
		}
		return false;
	}

	void Window::update()
	{
		platformUpdate();
	}

	void Window::close()
	{
		if (m_state == State::Open)
		{
			m_state = State::Closing;
		}
	}
}
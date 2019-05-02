#include "application.h"

#include "input.h"
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

	Input* Application::getInput() const
	{
		return m_input;
	}

	Time* Application::getTime() const
	{
		return m_time;
	}

	Window* Application::getWindow() const
	{
		return m_window;
	}

	bool Application::startup()
	{
		m_window = initializeWindow();
		m_input = initializeInput();
		m_time = initializeTime();
	}

	void Application::shutdown()
	{

	}

	void Application::tick()
	{

	}
}
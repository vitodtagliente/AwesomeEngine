#include <awesome/core/application.h>
#include <awesome/core/time.h>
#include <awesome/core/timer.h>
#include <awesome/core/log.h>

namespace awesome
{
	Application* Application::m_Instance = nullptr;

	Application::Application(const std::string& name, const WindowProperties& properties)
	{
		m_Window = new Window(name, properties);
		m_UpdateTime = 1000.0f / 60.0f;
	}

	Application::~Application()
	{
		Time::free();
		delete m_Window;
	}

	void Application::update()
	{
		// update the scene and objects
	}

	void Application::updateFPS()
	{
		m_LastFPS = m_FPS;
		m_FPS = 1;

		log(LogSeverity::Log, "FPS: " + std::to_string(m_LastFPS));
	}

	void Application::render()
	{
		++m_FPS;

		// rendering pass
	}

	void Application::launch() {
		assert(m_Window != nullptr);

		// open the main window
		m_Window->open();

		if(m_Window->getState() == WindowState::Open)
		{

		}

		// init application behaviours
		for (auto behaviour : m_Behaviours)
		{
			if (behaviour)
				behaviour->init();
		}

		// define timed operations

		// update operation
		Timer update_timer(getUpdateTime(), std::bind(&Application::update, this), true);
		// rendering operation
		Timer render_timer(getRenderTime(), std::bind(&Application::render, this), true);
		// fps counter
		Timer one_second_timer(1.0f, std::bind(&Application::updateFPS, this), true);

		// start the timers
		update_timer.start();
		render_timer.start();
		one_second_timer.start();

		// the application is running
		m_State = ApplicationState::Running;

		// application lifetime cycle
		while (m_Window->getState() == WindowState::Open)
		{			
			// application content update
			for (auto behaviour : m_Behaviours)
			{
				if (behaviour && behaviour->isActive())
					behaviour->update();
			}

			// update the window 
			m_Window->update();

			// core systems update
			Time::instance()->tick();
			Log::instance()->flush();
		}

		update_timer.stop();
		render_timer.stop();
		one_second_timer.stop();

		// uninit application behaviours
		for (auto behaviour : m_Behaviours)
		{
			if (behaviour)
				behaviour->uninit();
		}

		// application closed
		m_State = ApplicationState::Closed;
	}

	void Application::pause()
	{
		if(m_State == ApplicationState::Running)
		{
			Time::instance()->pause();
			m_State = ApplicationState::Pause;
		}
	}

	void Application::resume()
	{
		if (m_State == ApplicationState::Pause)
		{
			Time::instance()->resume();
			m_State = ApplicationState::Running;
		}
	}

	void Application::close()
	{
		if (m_Window)
		{
			m_Window->close();
			m_State = ApplicationState::Closing;
		}
	}
}
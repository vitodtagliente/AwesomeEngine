#pragma once

#include <memory>
#include "../engine/module.h"

namespace awesome
{
	class Application;
	class Input;
	class Time;
	class Window;

	class ApplicationModule : public Module
	{
	public:

		ApplicationModule();
		~ApplicationModule();

		inline Application* const getApplication() const { return m_application; }
		inline Input* const getInput() const { return m_input; }
		inline Time* const getTime() const { return m_time; }
		inline Window* const getWindow() const { return m_window; }

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		// initialize the module elements
		virtual bool initialize() = 0;
		
		// application
		Application* m_application;
		// input
		Input* m_input;
		// time
		Time* m_time;
		// window
		Window* m_window;

	};
}
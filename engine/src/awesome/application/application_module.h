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

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		// initialize the module elements
		virtual void initialize() = 0;
		
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
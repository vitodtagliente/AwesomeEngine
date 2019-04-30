#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Input;
	class Time;
	class Window;

	class Application : public Module<Application>
	{
	public:

		Application();
		virtual ~Application();
		
		virtual bool startup() override;
		virtual void shutdown() override;

		virtual void tick(const double t_deltaTime = 0.0) override;

		// get the main window
		Window* getWindow() const;

	protected:

		// application's input
		Input* m_input;
		// application's time
		Time* m_time;
		// application's window
		Window* m_window;

	};
}
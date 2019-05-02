#pragma once

#include "../engine/singleton.h"

namespace awesome
{
	class Input;
	class Time;
	class Window;

	class Application : public Singleton<Application>
	{
	public:

		friend class Engine;

		Application();
		virtual ~Application();

		// get the input system
		Input* getInput() const;
		// get the time system
		Time* getTime() const;
		// get the main window
		Window* getWindow() const;

	protected:

		// called by the engine
		virtual bool startup();
		virtual void shutdown();
		virtual void tick();

		virtual Input* initializeInput() const = 0;
		virtual Time* initializeTime() const = 0;
		virtual Window* initializeWindow() const = 0;

		// application's input
		Input* m_input;
		// application's time
		Time* m_time;
		// application's window
		Window* m_window;

	};
}
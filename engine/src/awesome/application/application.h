#pragma once

#include <initializer_list>
#include "../engine/module.h"

namespace awesome
{
	class Input;
	class Time;
	class Window;
	class IModule;
	class ModuleManager;

	class Application : public Module<Application>
	{
	public:

		Application();
		virtual ~Application();

		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;
		
		// get the input system
		inline Input* getInput() const { return m_input; }
		// get the time system
		inline Time* getTime() const { return m_time; }
		// get the main window
		inline Window* getWindow() const { return m_window; }

	protected:
		
		virtual std::initializer_list<IModule*> getModulesToRegister() const = 0;

		// module's manager
		ModuleManager* m_moduleManager;

		// application's input
		Input* m_input;
		// application's time
		Time* m_time;
		// application's window
		Window* m_window;

	};
}
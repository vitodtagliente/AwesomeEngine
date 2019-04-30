#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Window;

	class Application : public Module<Application>
	{
	public:

		Application();
		virtual ~Application();

		// get the main window
		Window* getWindow() const;

	private:

		// application's window
		Window* m_window;

	};
}
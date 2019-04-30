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
		
		virtual bool startup() override;
		virtual void shutdown() override;

		// get the main window
		Window* getWindow() const;

	protected:

		// application's window
		Window* m_window;

	};
}
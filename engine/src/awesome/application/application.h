#pragma once

#include <memory>
#include <awesome/core/singleton.h>
#include "application_module.h"

namespace awesome
{
	class ApplicationAPI;
	class Window;

	class Application : public Singleton<Application>
	{
	public:
		
		Application(const ApplicationModule::API& t_api);
		virtual ~Application();

		virtual bool initialize();
		virtual void update();
		virtual void close();

		const Window& getWindow() const { return *m_window; }

	protected:

		// api 
		const ApplicationModule::API& m_api;
		// window
		std::unique_ptr<Window> m_window;
	};
}
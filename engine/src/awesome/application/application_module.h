#pragma once

#include <awesome/engine/module.h>

namespace awesome
{
	class ApplicationAPI;
	class Application;

	class ApplicationModule : public Module
	{
	public:

		ApplicationModule();
		virtual ~ApplicationModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		virtual ApplicationAPI* const createAPI() const = 0;

		// api
		ApplicationAPI* m_api;
		// application
		Application* m_application;

	};
}
#pragma once

/*
 * Copyright 2019 Vito Domenico Tagliente. All rights reserved.
 * Application Module
 */

#include <memory>
#include <awesome/core/api_wrapper.h>
#include <awesome/core/engine.h>

namespace awesome
{
	class Application;
	class Window;

	class ApplicationModule : public Engine::Module
	{
	public:

		// Application API abstraction
		class API : public APIWrapper
		{
		public:
			API() = default;
			virtual ~API() = default;

			virtual std::unique_ptr<Application> make_application() const = 0;
			virtual std::unique_ptr<Window> make_window() const = 0;
		};

		ApplicationModule();
		virtual ~ApplicationModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		// create the appropriate api
		virtual std::unique_ptr<API> make_api() const = 0;

	private:

		// api
		std::unique_ptr<API> m_api;
		// input system
		std::unique_ptr<Application> m_application;

	};
}
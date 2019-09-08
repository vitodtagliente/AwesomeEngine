#pragma once

#include <awesome/application/application_module.h>

namespace awesome
{
	class ApplicationModuleGLFW : public ApplicationModule
	{
	public:

		class API_GLFW : public API
		{
		public:

			virtual bool startup() override;
			virtual void shutdown() override;

			virtual std::unique_ptr<Application> make_application() const override;
			virtual std::unique_ptr<Window> make_window() const override;
		};

		ApplicationModuleGLFW();
		virtual ~ApplicationModuleGLFW() override;

	protected:

		// create the input api
		virtual std::unique_ptr<API> make_api() const override;

		virtual bool startup_implementation() override;

	};
}
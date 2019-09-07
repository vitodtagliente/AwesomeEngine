#pragma once

#include <awesome/input/input_module.h>

namespace awesome
{
	class InputModuleGLFW : public InputModule
	{
	public:

		class API_GLFW : public API
		{
		public:

			virtual bool startup() override;
			virtual void shutdown() override;
		};

		InputModuleGLFW();
		virtual ~InputModuleGLFW() override;

	protected:

		// create the input api
		virtual API* const createAPI() const override;

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;

	private:

		void bindWindowEvents();
		void unbindWindowEvents();

	};
}
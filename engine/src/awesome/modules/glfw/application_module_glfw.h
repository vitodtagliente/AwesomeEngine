#pragma once

#include <awesome/application/application_module.h>

namespace awesome
{
	class ApplicationModuleGLFW final : public ApplicationModule
	{
	private:

		virtual bool startup_implementation() override;

		virtual ApplicationAPI* const createAPI() const override;
	};
}
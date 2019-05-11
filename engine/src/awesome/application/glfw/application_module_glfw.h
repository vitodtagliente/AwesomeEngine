#pragma once

#include "../application_module.h"

namespace awesome
{
	class ApplicationModuleGLFW final : public ApplicationModule
	{
	public:

		virtual void initialize() override;

	private:

		virtual bool startup_implementation() override;
	};
}
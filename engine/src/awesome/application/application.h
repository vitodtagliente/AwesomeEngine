#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Application : public Module<Application>
	{
	public:

		// register the application specific engine modules
		virtual void registerModules() = 0;

	protected:
		
		// module interface
		virtual bool startup_imp() override;

	};
}
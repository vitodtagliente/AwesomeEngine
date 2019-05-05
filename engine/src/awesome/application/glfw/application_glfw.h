#pragma once

#include "../application.h"

namespace awesome 
{
	class ApplicationGLFW : public Application
	{		
	private:

		// module startup
		virtual bool startup_implementation() override;
		// register modules
		virtual void registerModules(class Engine* const t_engine);

	};
}
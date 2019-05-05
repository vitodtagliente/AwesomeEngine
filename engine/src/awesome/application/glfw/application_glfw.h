#pragma once

#include "../application.h"

namespace awesome 
{
	class ApplicationGLFW : public Application
	{		
	public:

		virtual void registerModules() override;

	private:

		// module startup
		virtual bool startup_implementation() override;
		virtual void update_implementation() override;

	};
}
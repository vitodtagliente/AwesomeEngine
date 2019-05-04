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
		virtual bool startup_imp() override;
		virtual void update_imp() override;

	};
}
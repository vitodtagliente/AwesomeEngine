#pragma once

#include "../application.h"

namespace awesome 
{
	class ApplicationGLFW : public Application
	{		
	private:

		// module startup
		virtual bool startup_imp() override;

	};
}
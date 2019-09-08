#pragma once

#include <awesome/application/application.h>

namespace awesome 
{
	class ApplicationGLFW : public Application
	{	
	public:

		ApplicationGLFW(const ApplicationModule::API& t_api);
	};
}
#include "application_module_glfw.h"

// #todo 
#include <GLFW/glfw3.h>

#include "application_api_glfw.h"

namespace awesome
{
	bool ApplicationModuleGLFW::startup_implementation()
	{
		if (glfwInit())
		{
			// #todo: bad code
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			return ApplicationModule::startup_implementation();
		}
		return false;
	}
	
	ApplicationAPI* const ApplicationModuleGLFW::createAPI() const
	{
		return new ApplicationAPI_GLFW();
	}
}
#include "application_module_glfw.h"

#include <GLFW/glfw3.h>

namespace awesome
{
	ApplicationModuleGLFW::ApplicationModuleGLFW()
		: ApplicationModule()
	{
	}

	ApplicationModuleGLFW::~ApplicationModuleGLFW()
	{
	}

	std::unique_ptr<ApplicationModule::API> ApplicationModuleGLFW::make_api() const
	{
		return std::make_unique<API_GLFW>();
	}

	bool ApplicationModuleGLFW::startup_implementation()
	{
		if (glfwInit())
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			return ApplicationModule::startup_implementation();
		}
		return false;
	}
}
#include "application_module_glfw.h"

#include <GLFW/glfw3.h>

#include "application_glfw.h"
#include "input_glfw.h"
#include "time_glfw.h"
#include "window_glfw.h"

namespace awesome
{
	bool ApplicationModuleGLFW::initialize()
	{
		m_application = new ApplicationGLFW();
		m_input = new InputGLFW();
		m_time = new TimeGLFW();
		m_window = new WindowGLFW();
		return true;
	}

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
}
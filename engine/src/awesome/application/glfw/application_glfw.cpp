#include "application_glfw.h"

#include <GLFW/glfw3.h>
#include "window_glfw.h"

namespace awesome
{
	ApplicationGLFW::ApplicationGLFW()
	{
	}

	ApplicationGLFW::~ApplicationGLFW()
	{
	}

	bool ApplicationGLFW::startup()
	{
		Application::startup();

		if (!glfwInit())
		{
			// cannot initialize the GLFW library
			return false;
		}
		// initialize the main window
		m_window = new WindowGLFW();
		return true;
	}

	void ApplicationGLFW::shutdown()
	{
		Application::shutdown();

	}
}
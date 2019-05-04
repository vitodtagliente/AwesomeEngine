#include "application_glfw.h"

#include <GLFW/glfw3.h>
#include "window_glfw.h"

namespace awesome
{
	bool ApplicationGLFW::startup_imp()
	{
		return glfwInit();
	}
}
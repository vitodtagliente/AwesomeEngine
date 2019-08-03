#include "time_glfw.h"

#include <GLFW/glfw3.h>
#include "window_glfw.h"

namespace awesome
{
	double TimeGLFW::getTime_implementation() const
	{
		return glfwGetTime();
	}
}
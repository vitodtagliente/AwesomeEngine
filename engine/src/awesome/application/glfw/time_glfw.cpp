#include "time_glfw.h"

#include <GLFW/glfw3.h>

namespace awesome
{
	double TimeGLFW::getApplicationTime() const
	{
		return glfwGetTime();
	}
}
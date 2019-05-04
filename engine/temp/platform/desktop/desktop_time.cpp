#include <awesome/core/time.h>
#include <GLFW/glfw3.h>

namespace awesome
{
	double Time::platformGetTime() const
	{
		return glfwGetTime();
	}
}
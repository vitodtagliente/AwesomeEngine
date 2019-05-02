#include "time_glfw.h"

#include <GLFW/glfw3.h>
#include "window_glfw.h"

namespace awesome
{
	bool TimeGLFW::startup()
	{
		// be sure the window application is ready
		return dynamic_cast<WindowGLFW*>(Window::instance()) != nullptr;
	}

	void TimeGLFW::shutdown()
	{
	}

	double TimeGLFW::getApplicationTime() const
	{
		return glfwGetTime();
	}
}
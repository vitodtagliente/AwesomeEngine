#include <awesome/platform.h>

#ifdef PLATFORM_DESKTOP

#include <awesome/core/time.h>
#include <GLFW/glfw3.h>

namespace awesome
{
	void Time::platformTick() {
		m_Time = glfwGetTime();
	}
}

#endif 
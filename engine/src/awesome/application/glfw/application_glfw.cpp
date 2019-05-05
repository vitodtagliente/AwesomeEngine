#include "application_glfw.h"

#include <cassert>
#include <GLFW/glfw3.h>
#include "input_glfw.h"
#include "time_glfw.h"
#include "window_glfw.h"
#include "../../engine/engine.h"

namespace awesome
{

	bool ApplicationGLFW::startup_implementation()
	{
		if (glfwInit())
		{
			return Application::startup_implementation();
		}
		return false;
	}
	void ApplicationGLFW::registerModules(Engine* const t_engine)
	{
		t_engine->registerModule<Window>(new WindowGLFW());
		t_engine->registerModule<Time>(new TimeGLFW());
		t_engine->registerModule<Input>(new InputGLFW());
	}
}
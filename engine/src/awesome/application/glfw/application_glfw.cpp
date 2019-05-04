#include "application_glfw.h"

#include <cassert>
#include <GLFW/glfw3.h>
#include "input_glfw.h"
#include "time_glfw.h"
#include "window_glfw.h"
#include "../../engine/engine.h"

namespace awesome
{
	void ApplicationGLFW::registerModules()
	{
		Engine* engine = Engine::instance();
		assert(engine != nullptr);

		engine->registerModule<Window>(new WindowGLFW());
		engine->registerModule<Time>(new TimeGLFW());
		engine->registerModule<Input>(new InputGLFW());
	}

	bool ApplicationGLFW::startup_imp()
	{
		return glfwInit();
	}

	void ApplicationGLFW::update_imp()
	{
	}
}
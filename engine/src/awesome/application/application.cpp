#include "application.h"

#include <cassert>
#include "../engine/engine.h"
#include "window.h"

namespace awesome
{
	Application::Application()
		: m_state(State::Unknown)
	{
	}

	bool Application::startup_implementation()
	{
		Engine* const engine = Engine::instance();
		assert(engine != nullptr);

		registerModules(engine);

		m_state = State::Running;
		return true;
	}

	void Application::update_implementation()
	{
		if (Window::instance()->shouldClose())
		{

		}
	}
}
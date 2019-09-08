#include "engine.h"

#include <cassert>

namespace awesome
{
	bool Engine::Module::startup()
	{
		// Cannot call the startup method multiple times
		assert(m_state == State::Unknown);

		const bool success = startup_implementation();
		
		m_state = success ? State::Started : State::Error;
		return success;
	}

	void Engine::Module::shutdown()
	{
		// Cannot shutdown a module that was not started
		if (m_state == State::Started)
		{
			shutdown_implementation();
			m_state = State::Closed;
		}
	}
	void Engine::Module::update()
	{
		if (m_state == State::Started)
		{
			update_implementation();
		}
	}

	void Engine::Module::pre_rendering()
	{
		if (m_state == State::Started)
		{
			pre_rendering_implementation();
		}
	}

	void Engine::Module::render()
	{
		if (m_state == State::Started)
		{
			render_implementation();
		}
	}

	void Engine::Module::post_rendering()
	{
		if (m_state == State::Started)
		{
			post_rendering_implementation();
		}
	}
}
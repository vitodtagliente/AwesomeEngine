#include "module.h"

#include <cassert>

namespace awesome
{
	bool Module::startup()
	{
		// Cannot call the startup method multiple times
		assert(m_state == State::Unknown);

		const bool success = startup_implementation();
		
		m_state = success ? State::Started : State::Error;
		return success;
	}

	void Module::shutdown()
	{
		// Cannot shutdown a module that was not started
		if (m_state == State::Started)
		{
			shutdown_implementation();
			m_state = State::Closed;
		}
	}
	void Module::update()
	{
		if (m_state == State::Started)
		{
			update_implementation();
		}
	}
}
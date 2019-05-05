#include "module.h"

#include <cassert>

namespace awesome
{
	bool IModule::startup()
	{
		// Cannot call the startup method multiple times
		assert(m_moduleState == State::Unknown);
		
		m_moduleState = State::Initializing;

		const bool success = startup_implementation();
		
		m_moduleState = success ? State::Initialized : State::Error;
		return success;
	}

	void IModule::shutdown()
	{
		// Cannot shutdown a module that was not started up
		assert(m_moduleState != State::Unknown);
		
		if (m_moduleState != State::Error && m_moduleState != State::Uninitializing && m_moduleState != State::Uninitialized)
		{
			m_moduleState = State::Uninitializing;
			shutdown_implementation();
			m_moduleState = State::Uninitialized;
		}
	}
	void IModule::update()
	{
		update_implementation();
	}
}
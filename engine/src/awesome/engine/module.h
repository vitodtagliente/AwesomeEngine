#pragma once

#include "../core/singleton.h"

namespace awesome
{
	// generic Engine Module interface

	class Module
	{
	public:

		enum class State
		{
			Unknown,
			Error,
			Started,
			Closed
		};

		// module initialization 
		bool startup();
		void shutdown();
		// update the module
		void update();

		// get the module state
		inline State getState() const { return m_state; }

	protected:

		// module specific implementation interface
		virtual bool startup_implementation() { return true; }
		virtual void shutdown_implementation() {}
		virtual void update_implementation() {}

		// module state
		State m_state{ State::Unknown };

	};
}
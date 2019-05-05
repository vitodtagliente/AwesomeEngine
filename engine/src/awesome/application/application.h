#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Application : public Module<Application>
	{
	public:

		enum class State
		{
			Unknown,
			Running,
			Suspended,
			Closing,
			Closed
		};

		Application();

		inline State getState() const { return m_state; }
		inline bool isRunning() const 
		{ 
			return m_state == State::Running || m_state == State::Suspended || m_state == State::Closing;
		}
		
	protected:

		// module startup
		virtual bool startup_implementation() override;
		// module update
		virtual void update_implementation() override;

		// register the application specific modules
		virtual void registerModules(class Engine* const t_engine) = 0;

		// application state
		State m_state;
	};
}
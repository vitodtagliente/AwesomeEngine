#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Application : public Module<Application>
	{
	public:
		
		Application();

		inline bool isRunning() const { return m_isRunning; }
		
	protected:

		// module startup
		virtual bool startup_implementation() override;
		// module update
		virtual void update_implementation() override;

		// register the application specific modules
		virtual void registerModules(class Engine* const t_engine) = 0;

		// application running state
		bool m_isRunning;
	};
}
#pragma once

#include "../core/singleton.h"

namespace awesome
{
	// generic Engine Module interface

	class IModule
	{
	public:

		enum class State
		{
			Unknown,
			Error,
			Initializing,
			Initialized,
			Running,
			Uninitializing,
			Uninitialized
		};

		// module initialization 
		bool startup();
		void shutdown();
		// update the module
		void update();

		// get the module state
		inline State getModuleState() const { return m_moduleState; }
		// check if the module is available
		inline bool isModuleAvailable() const 
		{ 
			return m_moduleState == State::Initialized || m_moduleState == State::Running; 
		}

	protected:

		virtual bool startup_imp() { return true; }
		virtual void shutdown_imp() {}
		virtual void update_imp() = 0;

		// module state
		State m_moduleState{ State::Unknown };

	};

	template<typename T>
	class Module : public IModule, public Singleton<T>
	{

	};
}
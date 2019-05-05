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
			return m_moduleState == State::Initialized; 
		}

	protected:

		virtual bool startup_implementation() { return true; }
		virtual void shutdown_implementation() {}
		virtual void update_implementation() = 0;

		// module state
		State m_moduleState{ State::Unknown };

	};

	template<typename T>
	class Module : public IModule, public Singleton<T>
	{

	};
}
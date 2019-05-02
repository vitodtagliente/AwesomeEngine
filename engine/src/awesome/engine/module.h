#pragma once

#include "../core/singleton.h"

namespace awesome
{
	// generic Engine Module interface

	class IModule
	{
	public:

		// module initialization 
		virtual bool startup() = 0;
		virtual void shutdown() = 0;
		// update the module
		virtual void update() = 0;

	};

	template<typename T>
	class Module : public IModule, public Singleton<T>
	{

	};
}
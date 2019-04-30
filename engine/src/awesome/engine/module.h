#pragma once

#include "singleton.h"

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
		virtual void tick(const double t_deltaTime = 0.0) = 0;

	};

	template<typename T>
	class Module : public IModule, public Singleton<T>
	{

	};
}
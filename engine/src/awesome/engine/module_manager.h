#pragma once

#include <initializer_list>
#include <vector>

namespace awesome
{
	class IModule;

	class ModuleManager final
	{
	public:

		ModuleManager(const std::initializer_list<IModule*>& t_modules);
		~ModuleManager();

		bool startup();
		void shutdown();
		void update();
		
	private:

		// modules
		std::vector<IModule*> m_modules;

	};
}
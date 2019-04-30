#pragma once

#include <vector>

namespace awesome
{
	class ModuleManager final
	{
	public:

		ModuleManager();
		~ModuleManager();
		
	private:

		// modules
		std::vector<class IModule*> m_modules;

	};
}
#include "module_manager.h"

#include "module.h"

namespace awesome
{
	ModuleManager::ModuleManager(const std::initializer_list<IModule*>& t_modules)
		: m_modules(std::move(t_modules))
	{

	}

	ModuleManager::~ModuleManager()
	{
		for (const IModule* const module : m_modules)
		{
			delete module;
		}
	}

	bool ModuleManager::startup()
	{
		for (IModule* const module : m_modules)
		{
			if (!module->startup())
			{
				return false;
			}
		}
		return true;
	}

	void ModuleManager::shutdown()
	{
		for (IModule* const module : m_modules)
		{
			module->shutdown();
		}
	}

	void ModuleManager::update()
	{
		for (IModule* const module : m_modules)
		{
			module->update();
		}
	}
}
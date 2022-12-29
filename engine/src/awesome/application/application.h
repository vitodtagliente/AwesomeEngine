/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <awesome/core/singleton.h>

#include "application_module.h"
#include "application_settings.h"

namespace graphics
{
	class Renderer2D;
}

class Application : public Singleton<Application>
{
public:
	typedef ApplicationMode Mode;

	void init(const std::initializer_list<ApplicationModule*>& modules = {});
	int run();
	void exit();

	template <typename T = ApplicationModule>
	T* const registerModule()
	{
		T* const module = new T();
		m_modules.push_back(std::unique_ptr<ApplicationModule>(module));
		return module;
	}

	template <typename T = ApplicationModule>
	T* const findModule() const
	{
		for (const auto& mod : m_modules)
		{
			if (T* const found_mod = dynamic_cast<T*>(mod.get()))
			{
				return found_mod;
			}
		}
		return nullptr;
	}

	ApplicationSettings settings;

private:
	void initSettings();
	void registerDefaultModules();

	std::vector<std::unique_ptr<ApplicationModule>> m_modules;
};
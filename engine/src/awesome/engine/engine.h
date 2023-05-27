/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <awesome/core/singleton.h>

#include "engine_module.h"

class Engine : public Singleton<Engine>
{
public:
	struct Stats
	{
		unsigned int framerate{ 0 };

		void clear();
	};

	void exit();
	void init(const std::initializer_list<EngineModule*>& modules = {});
	int run();

	inline const Stats& getStats() const { return m_stats; }
	inline Stats& getStats() { return m_previousStats; }

	template <typename T = EngineModule>
	T* const registerModule()
	{
		T* const module = new T();
		m_modules.push_back(std::unique_ptr<EngineModule>(module));
		return module;
	}

	template <typename T = EngineModule>
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

private:
	void initSettings();
	void loadDefaultScene();
	void registerDefaultModules();

	std::vector<std::unique_ptr<EngineModule>> m_modules;
	Stats m_previousStats;
	Stats m_stats;
};
/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <array>
#include <cassert>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "module.h"

class Engine final
{
public:

	enum class Mode
	{
		Game,
		Server
	};

	Engine();
	~Engine();

	// launch the engine
	void launch(const Mode mode = Mode::Game);

	static Engine* const instance() { return s_instance; }

	template <typename T>
	void registerModule()
	{
		static_assert(std::is_base_of<Module, T>());
		registerModule(new T());
	}

	void registerModule(Module* const module)
	{
		m_modules.push_back(module);
	}

	template <typename T>
	T* const findModule()
	{
		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			T* const module = dynamic_cast<T*>(*it);
			if (module != nullptr)
				return module;
		}
		return nullptr;
	}

private:

	// engine startup and shutdown
	bool startup();
	void shutdown();
	// engine loop
	void update();
	void render();

	// register engine modules
	void registerModules(const Mode mode);

	// modules
	std::vector<Module*> m_modules;
	// singleton
	static Engine* s_instance;
};
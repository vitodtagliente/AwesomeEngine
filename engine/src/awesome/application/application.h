/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <memory>

#include <awesome/core/singleton.h>
#include <awesome/graphics/renderer.h>

#include "canvas.h"
#include "input.h"
#include "time.h"

class World;

class Application : public Singleton<Application>
{
public:

	class Module
	{
	public:
		virtual void startup() {}
		virtual void shutdown() {}
		virtual void update(double /*deltaTime*/) {}
		virtual void preRendering() {}
		virtual void render(graphics::Renderer& /*renderer*/) {}
		virtual void postRendering() {}
	};

	Application(const std::initializer_list<Module*> modules = {});
	virtual ~Application();

	int run();

	inline const Canvas& getCanvas() const { return m_canvas; }
	inline Canvas& getCanvas() { return m_canvas; }
	inline const Input& getInput() const { return m_input; }
	inline Input& getInput() { return m_input; }
	inline const Time& getTime() const { return m_time; }
	inline Time& getTime() { return m_time; }

	template <typename T = Module>
	std::vector<T*> getModules() const
	{
		std::vector<T*> found_modules;
		for (Module* const module : m_modules)
		{
			if (T* const found_module = dynamic_cast<T*>(module))
			{
				found_modules.push_back(found_module);
			}
		}
		return found_modules;
	}

	template <typename T = Module>
	T* const addModule()
	{
		T* const module = new T();
		m_modules.push_back(module);
		return module;
	}

private:
	void init();
	void update();
	void render();

	std::vector<Module*> m_modules;
	Canvas m_canvas;
	Input m_input;
	Time m_time;
};
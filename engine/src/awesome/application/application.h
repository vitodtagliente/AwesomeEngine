/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/data/asset_library.h>
#include <awesome/graphics/renderer.h>

#include "canvas.h"
#include "input.h"
#include "time.h"

class Application : public Singleton<Application>
{
public:

	struct Settings
	{

	};

	class Module
	{
	public:
		Module() = default;
		virtual ~Module() = default;
		virtual void startup() {}
		virtual void shutdown() {}
		virtual void update(double /*deltaTime*/) {}
		virtual void preRendering() {}
		virtual void render(graphics::Renderer* const /*renderer*/) {}
		virtual void postRendering() {}
	};

	Application(const std::initializer_list<Module*>& modules = {});
	virtual ~Application();

	int run();

	template <typename T = Module>
	T* const registerModule()
	{
		T* const module = new T();
		m_modules.push_back(std::unique_ptr<Module>(module));
		return module;
	}

private:
	void registerDefaultModules();

	std::vector<std::unique_ptr<Module>> m_modules;
	Canvas m_canvas;
	Input m_input;
	Time m_time;
	AssetLibrary m_assetLibrary;
};
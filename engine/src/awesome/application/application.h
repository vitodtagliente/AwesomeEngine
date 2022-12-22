/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <awesome/core/singleton.h>

#include "application_settings.h"

namespace graphics
{
	class Renderer2D;
}

class Application : public Singleton<Application>
{
public:

	typedef ApplicationMode Mode;

	class Module
	{
	public:
		Module() = default;
		virtual ~Module() = default;
		virtual void startup() {}
		virtual void shutdown() {}
		virtual void update(double /*deltaTime*/) {}
		virtual void preRendering() {}
		virtual void render(graphics::Renderer2D* const /*renderer*/) {}
		virtual void postRendering() {}
	};

	Application() = default;
	virtual ~Application() = default;

	void init(const std::initializer_list<Module*>& modules = {});
	int run();
	void exit();

	template <typename T = Module>
	T* const registerModule()
	{
		T* const module = new T();
		m_modules.push_back(std::unique_ptr<Module>(module));
		return module;
	}

	ApplicationSettings settings;

private:
	void initSettings();
	void registerDefaultModules();

	std::vector<std::unique_ptr<Module>> m_modules;
};
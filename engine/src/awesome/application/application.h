/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/singleton.h>
#include <awesome/graphics/renderer.h>

#include "time.h"

REFLECT_ENUM(ApplicationMode,
	Editor,
	Server,
	Standalone
)

class Application : public Singleton<Application>
{
public:

	typedef ApplicationMode Mode;

	struct Settings
	{
		Settings() = default;

		static Settings load(const std::filesystem::path& path);
		void save(const std::filesystem::path& path);

		ApplicationMode mode{ ApplicationMode::Editor };
		std::string workspacePath{ "../assets" };
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

	inline Mode getMode() const { return m_mode; }

	int run();
	void exit();

	template <typename T = Module>
	T* const registerModule()
	{
		T* const module = new T();
		m_modules.push_back(std::unique_ptr<Module>(module));
		return module;
	}

	Settings settings;

private:
	void registerDefaultModules();

	Mode m_mode;
	std::vector<std::unique_ptr<Module>> m_modules;
	Time m_time;
};
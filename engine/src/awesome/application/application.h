/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include <awesome/asset/scene_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/singleton.h>
#include <awesome/graphics/renderer.h>

#include "time.h"

REFLECT_ENUM(ApplicationMode,
	Editor,
	Server,
	Standalone
)

REFLECT_ENUM(FpsMode,
	Fps30 = 30,
	Fps60 = 60,
	Fps90 = 90,
	Unlimited
)

class Application : public Singleton<Application>
{
public:

	typedef ApplicationMode Mode;

	struct Settings
	{
		static Settings load(const std::filesystem::path& path);
		void save(const std::filesystem::path& path);

		FpsMode fps{ FpsMode::Fps60 };
		ApplicationMode mode{ ApplicationMode::Editor };
		std::filesystem::path workspacePath{ std::filesystem::current_path() / ".." / "assets" };

		SceneAssetPtr editorScene;
		SceneAssetPtr serverScene;
		SceneAssetPtr standaloneScene;
		std::string serverIp;
		int serverPort;
		int maxServerConnections;
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
		virtual void render(graphics::Renderer2D* const /*renderer*/) {}
		virtual void postRendering() {}
	};

	Application() = default;
	virtual ~Application() = default;

	inline const Settings& getSettings() const { return m_settings; }

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

private:
	void initSettings();
	void registerDefaultModules();

	std::vector<std::unique_ptr<Module>> m_modules;
	Settings m_settings;
	Time m_time;
};
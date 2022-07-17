#include <iostream>
#include "application.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/application/time.h>
#include <awesome/audio/audio.h>
#include <awesome/asset/asset_importer.h>
#include <awesome/asset/asset_library.h>
#include <awesome/core/timer.h>
#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>
#include <awesome/editor/editor_module.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/graphics_module.h>
#include <awesome/graphics/renderer.h>
#include <awesome/net/net_module.h>

#include "private/components_loader.h"

using namespace graphics;

void Application::init(const std::initializer_list<Module*>& modules)
{
	for (Module* const module : modules)
	{
		m_modules.push_back(std::unique_ptr<Module>(module));
	}
}

int Application::run()
{
	Canvas& canvas = Canvas::instance();
	Input& input = Input::instance();
	World& world = World::instance();

	if (!canvas.open())
	{
		return -1;
	}

	initSettings();
	registerDefaultModules();
	ComponentsLoader().load();

	for (const auto& module : m_modules)
	{
		module->startup();
	}

	Timer fpsTimer(1.f / static_cast<int>(m_settings.fps));
	double deltatime = 0.0;

	while (canvas.isOpen())
	{
		m_time.tick();
		fpsTimer.tick(m_time.getDeltaTime());
		deltatime += m_time.getDeltaTime();
		if (!fpsTimer.isExpired() && m_settings.fps != FpsMode::Unlimited) continue;

		fpsTimer.reset();
		canvas.update();

		for (const auto& module : m_modules)
		{
			module->update(deltatime);
		}

		input.update();
		world.update(deltatime);

		// rendering
		{
			graphics::Renderer2D* const renderer = &graphics::Context::instance().renderer;
			for (const auto& module : m_modules)
			{
				module->preRendering();
			}

			world.render(renderer);

			for (const auto& module : m_modules)
			{
				module->render(renderer);
			}

			for (const auto& module : m_modules)
			{
				module->postRendering();
			}
		}

		world.flush();
		deltatime = 0.0;
	}

	for (const auto& module : m_modules)
	{
		module->shutdown();
	}

	return 0;
}

void Application::exit()
{
	Canvas::instance().close();
}

void Application::initSettings()
{
	bool reload = false;
	const std::filesystem::path settingsPath = std::filesystem::current_path() / "settings.json";
	if (std::filesystem::exists(settingsPath))
	{
		m_settings = Settings::load(settingsPath);
		reload = true;
	}

	AssetImporter importer;
	importer.import(m_settings.workspacePath, true);
	AssetLibrary::instance().m_directory = m_settings.workspacePath;

	if (reload)
	{
		m_settings = Settings::load(settingsPath);
	}

	SceneAssetPtr sceneToLoad;
	switch (m_settings.mode)
	{
	case Mode::Editor: sceneToLoad = m_settings.editorScene; break;
	case Mode::Server: sceneToLoad = m_settings.serverScene; break;
	case Mode::Standalone: sceneToLoad = m_settings.standaloneScene; break;
	}

	if (sceneToLoad)
	{
		if (sceneToLoad->data.has_value())
		{
			World::instance().load(sceneToLoad);
		}
		else
		{
			sceneToLoad->onLoad = [sceneToLoad]() -> void
			{
				World::instance().load(sceneToLoad);
			};
		}
	}
}

void Application::registerDefaultModules()
{
	if (m_settings.mode != Mode::Server)
	{
		registerModule<Audio>();
		registerModule<graphics::Module>();
	}

	if (m_settings.mode == Mode::Editor)
	{
		registerModule<editor::Module>();
	}

	// common modules
	registerModule<net::Module>();
}

Application::Settings Application::Settings::load(const std::filesystem::path& path)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Settings settings;
	json::value data = json::Deserializer::parse(read(path));
	if (data.contains("fps"))
	{
		stringToEnum(data["fps"].as_string(""), settings.fps);
	}
	if (data.contains("mode"))
	{
		stringToEnum(data["mode"].as_string(""), settings.mode);
	}
	if (data.contains("workspacePath"))
	{
		settings.workspacePath = data["workspacePath"].as_string("");
	}

	if (data.contains("editorScene"))
	{
		const uuid id(data["editorScene"].as_string());
		settings.editorScene = AssetLibrary::instance().find<SceneAsset>(id);
	}
	if (data.contains("serverScene"))
	{
		const uuid id(data["serverScene"].as_string());
		settings.serverScene = AssetLibrary::instance().find<SceneAsset>(id);
	}
	if (data.contains("standaloneScene"))
	{
		const uuid id(data["standaloneScene"].as_string());
		settings.standaloneScene = AssetLibrary::instance().find<SceneAsset>(id);
	}

	return settings;
}

void Application::Settings::save(const std::filesystem::path& path)
{
	const json::value& data = json::object({
			{"fps", enumToString(fps)},
			{"mode", enumToString(mode)},
			{"editorScene", editorScene ? static_cast<std::string>(editorScene->descriptor.id) : ""},
			{"serverScene", serverScene ? static_cast<std::string>(serverScene->descriptor.id) : ""},
			{"standaloneScene", standaloneScene ? static_cast<std::string>(standaloneScene->descriptor.id) : ""},
			{"workspacePath", workspacePath.string()}
		});

	Archive archive(path, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
}
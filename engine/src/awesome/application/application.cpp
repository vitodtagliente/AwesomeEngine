#include <iostream>
#include "application.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/application/time.h>
#include <awesome/audio/audio.h>
#include <awesome/asset/asset_importer.h>
#include <awesome/asset/asset_library.h>
#include <awesome/core/serialization.h>
#include <awesome/core/timer.h>
#include <awesome/data/archive.h>
#include <awesome/data/json_file.h>
#include <awesome/encoding/json.h>
#include <awesome/editor/editor_module.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/graphics_module.h>
#include <awesome/graphics/renderer.h>
#include <awesome/player/player.h>
#include <awesome/net/net_module.h>

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
	Time time;
	Canvas& canvas = Canvas::instance();
	Input& input = Input::instance();
	World& world = World::instance();

	if (!canvas.open())
	{
		return -1;
	}

	initSettings();
	registerDefaultModules();

	for (const auto& module : m_modules)
	{
		module->startup();
	}

	// initialize the local player
	// there's always a player at index 0
	Player player(
		PlayerIndex::Player0,
		TypeFactory::instantiate<PlayerController>(settings.playerControllerType.value.empty() ? "PlayerController" : settings.playerControllerType.value),
		TypeFactory::instantiate<PlayerState>(settings.playerStateType.value.empty() ? "PlayerState" : settings.playerControllerType.value)
	);

	Timer fpsTimer(1.f / static_cast<int>(settings.fps));
	double deltatime = 0.0;

	while (canvas.isOpen())
	{
		time.tick();
		fpsTimer.tick(time.getDeltaTime());
		deltatime += time.getDeltaTime();
		if (!fpsTimer.isExpired() && settings.fps != FpsMode::Unlimited) continue;

		fpsTimer.reset();
		canvas.update();

		for (const auto& module : m_modules)
		{
			module->update(deltatime);
		}

		input.update();
		world.update(deltatime, settings.quadspaceBounds);

		// rendering
		{
			graphics::Renderer2D* const renderer = &graphics::Context::instance().renderer;
			for (const auto& module : m_modules)
			{
				module->preRendering();
			}

			world.render(renderer, settings.wireframesEnabled, settings.wireframesColor);

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
	reload = JsonFile::load(settingsPath, settings);

	AssetImporter importer;
	importer.import(settings.workspacePath, true);
	AssetLibrary::instance().m_directory = settings.workspacePath;

	if (reload)
	{
		JsonFile::load(settingsPath, settings);
	}

	SceneAssetPtr sceneToLoad;
	switch (settings.mode)
	{
	case Mode::Editor: sceneToLoad = settings.editorScene; break;
	case Mode::Server: sceneToLoad = settings.serverScene; break;
	case Mode::Standalone: sceneToLoad = settings.standaloneScene; break;
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
	if (settings.mode != Mode::Server)
	{
		registerModule<Audio>();
		registerModule<graphics::Module>();
	}

	if (settings.mode == Mode::Editor)
	{
		registerModule<editor::Module>();
	}

	// common modules
	registerModule<net::Module>();
}
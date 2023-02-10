#include <iostream>
#include "engine.h"

#include <awesome/engine/canvas.h>
#include <awesome/engine/input.h>
#include <awesome/engine/time.h>
#include <awesome/core/timer.h>

void Engine::init(const std::initializer_list<EngineModule*>& modules)
{
	for (EngineModule* const module : modules)
	{
		m_modules.push_back(std::unique_ptr<EngineModule>(module));
	}
}

int Engine::run()
{
	// AssetLibrary& library = AssetLibrary::instance();
	Canvas& canvas = Canvas::instance();
	Input& input = Input::instance();
	Time time;
	// World& world = World::instance();

	if (!canvas.open())
	{
		return -1;
	}

	initSettings();
	// canvas.setTitle(settings.name);

	registerDefaultModules();

	for (const auto& module : m_modules)
	{
		module->startup();
	}

	// initialize the local player
	// there's always a player at index 0
	// Player::initialize(
	// 	PlayerIndex::Player0,
	// 	settings.player->playerControllerType.value.empty() ? "PlayerController" : settings.player->playerControllerType.value,
	// 	settings.player->playerStateType.value.empty() ? "PlayerState" : settings.player->playerStateType.value
	// );

	Timer fpsTimer(1.f / static_cast<int>(settings.fps));
	Timer statsTimer(1.f);
	double deltaTime = 0.0;

	while (canvas.isOpen())
	{
		time.tick();
		fpsTimer.tick(time.getDeltaTime());
		statsTimer.tick(time.getDeltaTime());
		deltaTime += time.getDeltaTime();

		if (!fpsTimer.isExpired() && settings.fps != FpsMode::Unlimited) continue;

		fpsTimer.reset();

		if (settings.mode == EngineMode::Editor)
		{
			// canvas.setTitle("[AwesomeEngine::Editor " + std::to_string(getStats().framerate) + " FPS] " + settings.name);
		}
		canvas.update();

		for (const auto& module : m_modules)
		{
			module->update(deltaTime);
		}

		input.update();
		// world.update(deltaTime);

		// rendering
		{
			for (const auto& module : m_modules)
			{
				module->preRendering();
			}

			for (const auto& module : m_modules)
			{
				module->render();
			}

			for (const auto& module : m_modules)
			{
				module->postRendering();
			}
		}

		// library.flush();
		// world.flush();
		deltaTime = 0.0;

		++m_stats.framerate;
		if (statsTimer.isExpired())
		{
			m_previousStats = m_stats;
			m_stats.clear();
			statsTimer.reset();
		}
	}

	for (const auto& module : m_modules)
	{
		module->shutdown();
	}

	return 0;
}

void Engine::exit()
{
	Canvas::instance().close();
}

void Engine::initSettings()
{
	/*
	bool reload = false;
	const std::filesystem::path settingsPath = std::filesystem::current_path() / ApplicationSettings::filename;
	reload = JsonFile::load(settingsPath, settings);

	AssetLibrary::instance().init(settings.workspacePath);
	AssetImporter importer;
	importer.import(settings.workspacePath, true);

	if (reload)
	{
		JsonFile::load(settingsPath, settings);
	}

	SceneAssetPtr sceneToLoad;
	switch (settings.mode)
	{
	case Mode::Editor: sceneToLoad = settings.scene->editorScene; break;
	case Mode::Server: sceneToLoad = settings.scene->serverScene; break;
	case Mode::Standalone: sceneToLoad = settings.scene->standaloneScene; break;
	}

	if (sceneToLoad != nullptr)
	{
		if (sceneToLoad->state == Asset::State::Ready)
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
	*/
}

void Engine::registerDefaultModules()
{
	/*
	if (settings.mode != Mode::Server)
	{
		registerModule<Audio>();
		registerModule<Graphics>();
		registerModule<UI>();
	}

	if (settings.mode == Mode::Editor)
	{
		registerModule<Editor>();
	}
	*/
}

void Engine::Stats::clear()
{
	framerate = 0;
}

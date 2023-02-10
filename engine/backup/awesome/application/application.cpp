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
#include <awesome/editor/editor.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/graphics.h>
#include <awesome/player/player.h>
#include <awesome/ui/ui.h>

using namespace graphics;

void Application::init(const std::initializer_list<ApplicationModule*>& modules)
{
	for (ApplicationModule* const module : modules)
	{
		m_modules.push_back(std::unique_ptr<ApplicationModule>(module));
	}
}

int Application::run()
{
	AssetLibrary& library = AssetLibrary::instance();
	Canvas& canvas = Canvas::instance();
	Input& input = Input::instance();
	Time time;
	World& world = World::instance();

	if (!canvas.open())
	{
		return -1;
	}

	initSettings();
	canvas.setTitle(settings.name);

	registerDefaultModules();

	for (const auto& module : m_modules)
	{
		module->startup();
	}

	// initialize the local player
	// there's always a player at index 0
	Player::initialize(
		PlayerIndex::Player0,
		settings.player->playerControllerType.value.empty() ? "PlayerController" : settings.player->playerControllerType.value,
		settings.player->playerStateType.value.empty() ? "PlayerState" : settings.player->playerStateType.value
	);

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

		if (settings.mode == ApplicationMode::Editor)
		{
			canvas.setTitle("[AwesomeEngine::Editor " + std::to_string(getStats().framerate) + " FPS] " + settings.name);
		}
		canvas.update();

		for (const auto& module : m_modules)
		{
			module->update(deltaTime);
		}

		input.update();
		world.update(deltaTime);

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

		library.flush();
		world.flush();
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

void Application::exit()
{
	Canvas::instance().close();
}

void Application::initSettings()
{
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
}

void Application::registerDefaultModules()
{
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
}

void Application::Stats::clear()
{
	framerate = 0;
}
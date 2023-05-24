#include "engine.h"

#include <iostream>
#include <future>
#include <queue>

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/components/component_register.h>
#include <awesome/ecs/entities_coordinator.h>
#include <awesome/engine/canvas.h>
#include <awesome/engine/input.h>
#include <awesome/engine/time.h>
#include <awesome/core/timer.h>
#include <awesome/scene/scene_graph.h>

#include <awesome/audio/audio_module.h>
#include <awesome/collision/collision.h>
#include <awesome/editor/editor.h>
#include <awesome/graphics/graphics.h>
#include <awesome/ui/ui.h>

class TaskList
{
public:
	void push(std::future<void>& task)
	{
		m_tasks.push(std::move(task));
	}

	void push(std::future<void>&& task)
	{
		m_tasks.push(std::move(task));
	}

	void wait()
	{
		while (!m_tasks.empty())
		{
			std::future<void>& task = m_tasks.front();
			task.wait();
			m_tasks.pop();
		}
	}

private:
	std::queue<std::future<void>> m_tasks;
};

void Engine::init(const std::initializer_list<EngineModule*>& modules)
{
	EntitiesCoordinator::instance().Init();
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
	SceneGraph& scenegraph = SceneGraph::instance();

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

	const EngineMode mode = settings.mode;

	// load the default scene
	SceneGraph::instance().load(
		mode == EngineMode::Editor
		? settings.scene.editor
		: mode == EngineMode::Standalone ? settings.scene.standalone : settings.scene.server
	);

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

		// update the modules
		{
			//TaskList tasks;
			for (const auto& module : m_modules)
			{
				//tasks.push(std::async(std::launch::async, [&module, deltaTime]() -> void
					//{
						module->update(deltaTime);
					//}
				//));
			}
			//tasks.wait();
		}

		input.update();
		scenegraph.update(deltaTime);

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

		scenegraph.flush();
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
	const std::filesystem::path workspace = std::filesystem::current_path() / "../assets";

	AssetLibrary& library = AssetLibrary::instance();
	library.init(workspace);

	{
		bool newFilesFound = false;
		const bool recursiveSearch = true;
		AssetImporter::import(workspace, recursiveSearch, newFilesFound);
		if (newFilesFound)
		{
			library.database.save();
		}
	}

	ComponentRegister::execute();

	settings.load(workspace / EngineSettings::Filename);
}

void Engine::registerDefaultModules()
{
	if (settings.mode != Mode::Server)
	{
		registerModule<AudioModule>();
		registerModule<Graphics>();
		registerModule<UI>();
	}

	if (settings.mode == Mode::Editor)
	{
		registerModule<Editor>();
	}

	registerModule<Collision>();
}

void Engine::Stats::clear()
{
	framerate = 0;
}

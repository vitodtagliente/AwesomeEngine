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
	reload = JsonFile::load(settingsPath, m_settings);

	AssetImporter importer;
	importer.import(m_settings.workspacePath, true);
	AssetLibrary::instance().m_directory = m_settings.workspacePath;

	if (reload)
	{
		JsonFile::load(settingsPath, m_settings);
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
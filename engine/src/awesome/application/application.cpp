#include <iostream>
#include "application.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/application/time.h>
#include <awesome/audio/audio.h>
#include <awesome/asset/asset_library.h>
#include <awesome/core/timer.h>
#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>
#include <awesome/editor/editor.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/graphics.h>
#include <awesome/graphics/renderer.h>

#include "private/components_loader.h"

using namespace graphics;

Application::Application(const std::initializer_list<Module*>& modules)
	: settings()
	, m_mode(Mode::Editor)
	, m_modules()
	, m_time()
{
	for (Module* const module : modules)
	{
		m_modules.push_back(std::unique_ptr<Module>(module));
	}
}

Application::~Application()
{
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

	// settings setup
	{
		settings = Settings::load(std::filesystem::current_path() / "settings.json");
		m_mode = settings.mode;
		AssetLibrary::instance().m_directory = std::filesystem::current_path() / settings.workspacePath;
	}

	registerDefaultModules();
	ComponentsLoader().load();

	for (const auto& module : m_modules)
	{
		module->startup();
	}

	Timer fpsTimer(1.f / static_cast<int>(settings.fps));
	double deltatime = 0.0;

	while (canvas.isOpen())
	{
		m_time.tick();
		fpsTimer.tick(m_time.getDeltaTime());
		deltatime += m_time.getDeltaTime();
		if (!fpsTimer.isExpired() && settings.fps != FpsMode::Unlimited) continue;

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
			graphics::Renderer* const renderer = &graphics::Renderer::instance();
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

void Application::registerDefaultModules()
{
	if (m_mode != Mode::Server)
	{
		registerModule<Audio>();
		registerModule<graphics::Graphics>();
	}

	if (m_mode == Mode::Editor)
	{
		registerModule<editor::Editor>();
	}
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
	return settings;
}

void Application::Settings::save(const std::filesystem::path& path)
{
	const json::value& data = json::object({
			{"fps", enumToString(fps)},
			{"mode", enumToString(mode)},
			{"workspacePath", workspacePath}
		});

	Archive archive(path, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
}
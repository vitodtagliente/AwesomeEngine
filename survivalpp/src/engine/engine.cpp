#include "engine.h"

#include <execution>
#include <thread>

#include "engine/canvas.h"
#include "engine/engine_settings.h"
#include "engine/input.h"
#include "engine/time.h"

#include "core/timer.h"

#include "ecs/component_array.h"
#include "ecs/entity.h"

#include "collision/quad_tree.h"

#include "graphics/graphics_module.h"
#include "gameplay/player.h"

#include "components/systems/collider2d_system.h"
#include "components/systems/rigidbody2d_system.h"
#include "components/systems/sprite_animator_system.h"

void Engine::init(const std::initializer_list<EngineModule*>& modules)
{
	for (EngineModule* const module : modules)
	{
		m_modules.push_back(std::unique_ptr<EngineModule>(module));
	}
}

int Engine::run()
{
	Canvas& canvas = Canvas::instance();
	EngineSettings& settings = EngineSettings::instance();
	Input& input = Input::instance();
	Time time;

	QuadTree& quadtree = QuadTree::instance();

	std::thread render_thread(&Engine::render, this);

	if (!canvas.open())
	{
		return -1;
	}

	registerDefaultModules();
	registerDefaultSystems();

	PlayerManager player_manager;
	player_manager.connect();

	for (const auto& module : m_modules)
	{
		module->startup(m_render_systems, m_update_systems);
	}

	Timer statsTimer(1.f);
	double deltaTime = 0.0;

	while (canvas.isOpen())
	{
		time.tick();
		statsTimer.tick(time.getDeltaTime());
		deltaTime += time.getDeltaTime();

		canvas.setTitle("Survivalpp " + std::to_string(getStats().framerate) + " FPS]");

		canvas.update();
		input.update();

		player_manager.update(deltaTime);

		// update the modules
		{
			std::for_each(
				std::execution::seq,
				m_modules.begin(),
				m_modules.end(),
				[deltaTime](const std::unique_ptr<EngineModule>& engine_module) -> void { engine_module->update(deltaTime); }
			);

			m_update_systems.run(deltaTime);
		}

		// render
		{
			for (const auto& module : m_modules)
			{
				module->preRendering();
			}

			std::for_each(
				std::execution::seq,
				m_modules.begin(),
				m_modules.end(),
				[](const std::unique_ptr<EngineModule>& module) -> void { module->render(); }
			);

			m_render_systems.run(0);
			for (const auto& module : m_modules)
			{
				module->postRendering();
			}
		}

		EntityManager::flush();
		ComponentRegistry::flush();

		quadtree.clear();
		for (Rigidbody2D& body : ComponentArray<Rigidbody2D>::instance().data())
		{
			quadtree.insert({ &body });
		}

		deltaTime = 0.0;

		++m_stats.framerate;
		if (statsTimer.isExpired())
		{
			m_previousStats = m_stats;
			m_stats.clear();
			statsTimer.reset();
		}

		if (settings.fps != FpsMode::Unlimited)
		{
			const std::size_t fps_time = static_cast<std::size_t>(1000.f / static_cast<int>(settings.fps));
		}
	}

	render_thread.join();

	EntityManager::clear();

	for (std::vector<std::unique_ptr<EngineModule>>::reverse_iterator it = m_modules.rbegin(); it != m_modules.rend(); ++it)
	{
		(*it)->shutdown();
	}

	return 0;
}

void Engine::exit()
{
	Canvas::instance().close();
}

void Engine::registerDefaultModules()
{
	registerModule<GraphicsModule>();
}

void Engine::registerDefaultSystems()
{
	m_update_systems.push_back<Collider2DSystem>();
	m_update_systems.push_back<Rigidbody2DSystem>();
	m_update_systems.push_back<SpriteAnimatorSystem>();
}

void Engine::render()
{
	Canvas& canvas = Canvas::instance();

	// render
	while (canvas.isOpen())
	{
		
	}
}

void Engine::Stats::clear()
{
	framerate = 0;
}

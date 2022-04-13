#include <iostream>
#include "application.h"

#include <awesome/core/timer.h>
#include <awesome/editor/editor.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/graphics.h>
#include <awesome/graphics/renderer.h>

using namespace graphics;

Application::Application(const std::initializer_list<Module*>& modules)
	: m_modules()
	, m_canvas()
	, m_input()
	, m_time()
	, m_assetLibrary()
{
	registerDefaultModules();
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
	if (!m_canvas.open())
	{
		return -1;
	}
	
	World world;

	for (const auto& module : m_modules)
	{
		module->startup();
	}

	Timer fpsTimer(1.f / 60);
	double deltatime = 0.0;

	while (m_canvas.isOpen())
	{
		m_time.tick();
		fpsTimer.tick(m_time.getDeltaTime());
		deltatime += m_time.getDeltaTime();
		if (!fpsTimer.isExpired()) continue;

		fpsTimer.reset();
		m_canvas.update();
		
		for (const auto& module : m_modules)
		{
			module->update(deltatime);
		}
		
		m_input.update();
		world.update(deltatime);

		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
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

void Application::registerDefaultModules()
{
	registerModule<graphics::Graphics>();
	registerModule<editor::Editor>();
}

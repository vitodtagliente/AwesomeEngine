#include <iostream>
#include "application.h"

#include <awesome/core/timer.h>
#include <awesome/editor/editor.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/graphics.h>
#include <awesome/graphics/renderer.h>

using namespace graphics;

Application::Application(const std::initializer_list<Module*> modules)
	: m_modules()
	, m_canvas()
	, m_input()
	, m_time()
	, m_assetLibrary()
{
	registerModules();
	for (auto it = modules.begin(); it != modules.end(); ++it)
	{
		Module* const module = *it;
		m_modules.push_back(module);
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

	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		Module* const module = *it;
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
		m_input.update();
		world.update(deltatime);

		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
			for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
			{
				Module* const module = *it;
				module->preRendering();
			}

			world.render(renderer);

			for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
			{
				Module* const module = *it;
				module->render(renderer);
			}

			for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
			{
				Module* const module = *it;
				module->postRendering();
			}
		}		

		world.flush();
		deltatime = 0.0;
	}

	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		Module* const module = *it;
		module->shutdown();
	}

	return 0;
}

void Application::registerModules()
{
	addModule<graphics::Graphics>();
	addModule<editor::Editor>();
}

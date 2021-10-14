#include <iostream>
#include <glad/glad.h>
#include "application.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/graphics/color.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

#include <vdtmath/math.h>
#include <awesome/core/timer.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
#include <awesome/components/sprite_renderer.h>

#include <awesome/editor/editor.h>

using namespace graphics;

Application::Application(const std::initializer_list<Module*> modules)
	: m_modules()
{
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

	gladLoadGL();
	
	World m_world;

	Context context;
	graphics::Renderer renderer(context);

	registerModules();

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
		m_world.update(deltatime);

		renderer.begin();
		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			Module* const module = *it;
			module->preRendering();
		}

		m_world.render(&renderer);

		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			Module* const module = *it;
			module->render(&renderer);
		}

		renderer.flush();

		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			Module* const module = *it;
			module->postRendering();
		}

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
	addModule<editor::Editor>();
}

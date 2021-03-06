#include "engine.h"

// #todo
#include <awesome/modules/glfw/application/application_module_glfw.h>
#include <awesome/modules/glfw/input/input_module_glfw.h>
#include <awesome/application/window.h>
#include <awesome/modules/opengl/graphics_module_gl.h>
#include "scene_module.h"
#include <awesome/modules/editor/editor_module.h>

namespace awesome
{
	Engine::Engine()
		: m_time()
		, m_modules()
		, m_services()
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::run(const std::initializer_list<Module*>& t_modules)
	{
		Engine().launch(t_modules);
	}

	void Engine::launch(const std::initializer_list<Module*>& t_modules)
	{
		// register the application module
		// and all the engine modules
		if (startup(t_modules))
		{
			while (isRunning())
			{
				update();
				render();
			}
		}
		shutdown();
	}

	bool Engine::startup(const std::initializer_list<Module*>& t_modules)
	{
		// register the engine modules
		registerModules();

		// register extra modules
		for (auto it = t_modules.begin(); it != t_modules.end(); it++)
		{
			registerModule(*it);
		}

		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			Module* const module = it->second;
			if (!module->startup())
			{
				if (module->getState() == Module::State::Error)
				{
					// there was a critical error with a module
					return false;
				}
			}
		}
		return true;
	}

	void Engine::shutdown()
	{
		// shutdown modules in reverse order
		m_modules.reverse();

		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			Module* const module = it->second;
			module->shutdown();
		}
	}

	void Engine::update()
	{
		m_time.tick();

		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			Module* const module = it->second;
			module->update();
		}
	}

	void Engine::render()
	{
		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			Module* const module = it->second;
			module->pre_rendering();
		}
		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			Module* const module = it->second;
			module->render();
		}
		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			Module* const module = it->second;
			module->post_rendering();
		}
	}

	bool Engine::isRunning() const
	{
		return Window::instance()->isOpen();
	}

	void Engine::registerModules()
	{
		// #todo
		registerModule<ApplicationModule>(new ApplicationModuleGLFW());
		registerModule<InputModule>(new InputModuleGLFW());
		registerModule<GraphicsModule>(new GraphicsModuleGL());
		registerModule<SceneModule>(new SceneModule());
		registerModule<EditorModule>(new EditorModule());
	}
}
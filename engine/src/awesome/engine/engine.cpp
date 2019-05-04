#include "engine.h"

#include "../application/application.h"
#include "../application/window.h"
#include "module.h"

// #todo
#include "../application/glfw/application_glfw.h"

namespace awesome
{
	Engine::Engine()
		: m_application()
		, m_modules()
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::run(const std::initializer_list<IModule*>& t_modules)
	{
		auto engine = new Engine();
		engine->launch(t_modules);
		delete engine;
	}

	void Engine::launch(const std::initializer_list<IModule*>& t_modules)
	{
		// register the application module
		// and all the engine modules
		if (startup(t_modules))
		{
			while (isRunning())
			{
				update();
			}
		}
		shutdown();
	}

	bool Engine::startup(const std::initializer_list<IModule*>& t_modules)
	{
		m_application = new ApplicationGLFW();
		if (m_application->startup())
		{
			// register the application modules
			// (core modules such as Window, Time, Input)
			m_application->registerModules();
			
			// register the engine modules
			registerModules();

			// register extra modules
			for (auto it = t_modules.begin(); it != t_modules.end(); it++)
			{
				registerModule(*it);
			}

			for (auto it = m_modules.begin(); it != m_modules.end(); it++)
			{
				IModule* const module = it->second;
				if (!module->startup())
				{
					if (module->getModuleState() == IModule::State::Error)
					{
						// there was a critical error with a module
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	void Engine::shutdown()
	{
		// shutdown modules in reverse order
		m_modules.reverse();

		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			IModule* const module = it->second;
			module->shutdown();
		}

		m_application->shutdown();
		delete m_application;
	}

	void Engine::update()
	{
		m_application->update();
		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			IModule* const module = it->second;
			module->update();
		}
	}

	bool Engine::isRunning() const
	{
		// #todo: hardcoded
		return Window::instance()->getModuleState() != IModule::State::PendingUninitialize;
	}

	void Engine::registerModules()
	{
	}
}
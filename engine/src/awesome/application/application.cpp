#include "application.h"

#include <cassert>
#include "input.h"
#include "time.h"
#include "window.h"
#include "../engine/module_manager.h"
#include "../engine/module.h"

namespace awesome
{
	Application::Application()
		: m_moduleManager(),
		m_input(nullptr),
		m_time(nullptr),
		m_window(nullptr)
	{
	}

	Application::~Application()
	{
		delete m_input;
		delete m_window;
		delete m_time;
		delete m_moduleManager;
	}

	bool Application::startup()
	{
		m_moduleManager = new ModuleManager(getModulesToRegister());
		return m_moduleManager->startup();
	}

	void Application::shutdown()
	{
		m_moduleManager->shutdown();
	}

	void Application::update()
	{
		m_moduleManager->update();


	}
}
#include "engine.h"

Engine* Engine::s_instance{ nullptr };

Engine::Engine()
	: m_modules()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

Engine::~Engine()
{

}

void Engine::launch(const Mode mode)
{
	// register the engine modules
	registerModules(mode);
	// startup the engine
	if (startup())
	{
		while (true)
		{
			update();
			render();
		}
	}
	shutdown();
}

bool Engine::startup()
{
	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		const Module::State state = (*it)->startup();
		if (state == Module::State::FatalError)
		{
			return false;
		}
		else if (state == Module::State::Error)
		{
			m_modules.erase(it);
		}
	}
	return true;
}

void Engine::shutdown()
{
	// shutdown modules in reverse order
	std::reverse(m_modules.begin(), m_modules.end());
	for (auto it = m_modules.begin(); it != m_modules.end(); it++)
	{
		(*it)->shutdown();
	}
}

void Engine::update()
{
	// WindowModule* const window = findModule<WindowModule>();
	// const double deltaTime = window->getApplication()->getTime()->getDeltaTime();
	const double deltaTime = 0;

	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		(*it)->update(deltaTime);
	}
}

void Engine::render()
{
	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		if ((*it)->supportsRenderingPhase())
		{
			(*it)->beginRendering();
		}
	}

	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		if ((*it)->supportsRenderingPhase())
		{
			(*it)->render();
		}
	}

	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		if ((*it)->supportsRenderingPhase())
		{
			(*it)->endRendering();
		}
	}
}

void Engine::registerModules(const Mode mode)
{
	if (mode != Mode::Server)
	{

	}
}
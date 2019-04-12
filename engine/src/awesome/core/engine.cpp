#include <cassert>
#include "engine.h"
#include"game.h"
#include "window.h"

namespace awesome
{
	Engine* Engine::m_instance{ nullptr };

	Engine::Engine(Game* t_game)
		: m_game(t_game)
		, m_window(nullptr)
	{

	}

	Engine::~Engine()
	{
		delete m_window;
		delete m_game;
	}

	void Engine::launch()
	{
		assert(m_window == nullptr);

		m_window = new Window();
		Window::Settings window_settings{};
		// #todo: read settings from ini
		if (m_window->open(window_settings))
		{
			m_game->init();
			// engine lifetime cycle
			while (m_window->getState() != Window::State::Closing)
			{
				m_window->update();
				m_game->update();
			}
			m_game->uninit();
		}
		else
		{
			// error management
		}
	}
}
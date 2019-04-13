#include <cassert>
#include "engine.h"
#include"game.h"
#include "time.h"
#include "window.h"

namespace awesome
{
	Engine* Engine::m_instance{ nullptr };

	Engine::Engine(Game* t_game)
		: m_game(t_game)
		, m_time(nullptr)
		, m_window(nullptr)
	{

	}

	Engine::~Engine()
	{
		delete m_game;
		delete m_time;
		delete m_window;
	}

	void Engine::launch()
	{
		assert(m_window == nullptr);
		assert(m_time == nullptr);

		m_window = new Window();
		Window::Settings window_settings{};
		// #todo: read settings from ini
		if (m_window->open(window_settings))
		{
			m_time = new Time();

			m_game->init();
			// engine lifetime cycle
			while (m_window->getState() != Window::State::Closing)
			{
				m_window->update();
				m_game->update();

				// update
				m_time->tick();
			}
			m_game->uninit();
		}
		else
		{
			// error management
		}
	}
}
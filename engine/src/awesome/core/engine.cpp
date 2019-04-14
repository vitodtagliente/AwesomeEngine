#include <cassert>
#include "engine.h"
#include"game.h"
#include "input.h"
#include "time.h"
#include "window.h"

namespace awesome
{
	Engine* Engine::m_instance{ nullptr };

	Engine* Engine::getInstance()
	{
		return m_instance;
	}

	Engine::Engine(Game* t_game)
		: m_game(t_game)
		, m_input(nullptr)
		, m_time(nullptr)
		, m_window(nullptr)
	{

	}

	Engine::~Engine()
	{
		delete m_game;
		delete m_input;
		delete m_time;
		delete m_window;
	}

	void Engine::launch()
	{
		assert(m_input == nullptr);
		assert(m_window == nullptr);
		assert(m_time == nullptr);

		m_window = new Window();
		Window::Settings window_settings{};
		// #todo: read settings from ini
		if (m_window->open(window_settings))
		{
			m_input = new Input();
			m_time = new Time();

			m_input->init(m_window->getWindowHandler());
			m_game->init();
			// engine lifetime cycle
			while (m_window->getState() != Window::State::Closing)
			{
				m_window->update();
				m_input->update();

				// game update
				m_game->update();

				m_time->tick();
			}
			m_game->uninit();

			m_input->uninit();
		}
		else
		{
			// error management
		}
	}
}
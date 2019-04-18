#include <cassert>
#include "engine.h"
#include"game.h"
#include "input.h"
#include "time.h"
#include "window.h"
#include "../graphics/renderer.h"
#include "../data/color.h"

namespace awesome
{
	Engine::Engine(Game* t_game)
		: m_game(t_game)
		, m_input(nullptr)
		, m_renderer(nullptr)
		, m_time(nullptr)
		, m_window(nullptr)
	{

	}

	Engine::~Engine()
	{
		delete m_game;
		delete m_input;
		delete m_renderer;
		delete m_time;
		delete m_window;
	}

	void Engine::launch()
	{
		m_window = new Window();
		Window::Settings window_settings{};
		// #todo: read settings from ini
		if (m_window->open(window_settings))
		{
			m_input = new Input();
			m_time = new Time();
			m_renderer = new Renderer();

			m_input->init(m_window->getWindowHandler());
			m_renderer->init();
			m_game->init();
			// engine lifetime cycle
			while (m_window->getState() != Window::State::Closing)
			{
				m_time->tick();
				m_input->update();

				// game update
				m_game->update(m_time->getDeltaTime());
				m_game->draw();

				m_window->update();
			}
			m_game->uninit();
			m_input->uninit();
			m_renderer->uninit();
		}
		else
		{
			// error management
		}
	}
}
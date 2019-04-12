#include "game.h"

namespace awesome
{
	Game::Game()
		: m_state(State::Unknown)
	{

	}

	void Game::init()
	{
		m_state = State::Running;
	}

	void Game::update()
	{
	}

	void Game::uninit()
	{
	}

	void Game::end()
	{
		m_state = State::Ended;
	}
}

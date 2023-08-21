#include "game.h"

#include "game/components/systems/enemy_system.h"

bool Game::startup(SystemRegistry&, SystemRegistry& update_systems)
{
	m_mode.init();

	update_systems.push_back<EnemySystem>();

	return true;
}

void Game::shutdown()
{
}

void Game::update(double delta_time)
{
	m_mode.update(delta_time);
}

void Game::render()
{
	m_mode.render();
}

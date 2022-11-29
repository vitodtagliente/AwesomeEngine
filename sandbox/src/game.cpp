#include "game.h"
#include "data/game_settings.h"

void Game::startup()
{
	GameSettings::instance().load();
}

void Game::shutdown()
{
}
#include "game.h"
#include "components/health_component.h"
#include <awesome/ecs/entities_coordinator.h>

bool Game::startup()
{
	EntitiesCoordinator::instance().RegisterComponent<HealthComponent>();
	return true;
}

void Game::shutdown()
{
}
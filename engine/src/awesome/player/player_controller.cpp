#include "player_controller.h"

#include <awesome/entity/entity.h>

#include "player_state.h"

void PlayerController::init()
{
	m_state = getOwner()->findComponent<PlayerState>();
}

void PlayerController::possess(Entity* const entity)
{
	m_possessedEntity = entity;
}

void PlayerController::unposses()
{
	m_possessedEntity = nullptr;
}

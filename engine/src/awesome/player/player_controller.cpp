#include "player_controller.h"

void PlayerController::init()
{
	m_state->init();
}

void PlayerController::update(const double deltaTime)
{
	m_state->update(deltaTime);
}

void PlayerController::possess(Entity* const entity)
{
	m_possessedEntity = entity;
}

void PlayerController::unposses()
{
	m_possessedEntity = nullptr;
}

Entity* const PlayerController::getPossessedEntity() const
{
	return m_possessedEntity;
}

PlayerState* const PlayerController::getState() const
{
	return m_state.get();
}

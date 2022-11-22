/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/entity/entity.h>

#include "player_state.h"

class PlayerController
{
public:
	PlayerController(PlayerState* const state);
	virtual ~PlayerController() = default;

	virtual void init();
	virtual void update(double deltaTime);
	virtual void possess(Entity* const entity);
	virtual void unposses();

	Entity* const getPossessedEntity() const;
	PlayerState* const getState() const;

protected:
	Entity* m_possessedEntity;
	std::unique_ptr<PlayerState> m_state;
};
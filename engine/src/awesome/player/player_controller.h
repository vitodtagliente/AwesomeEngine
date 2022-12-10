/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/reflection.h>
#include <awesome/entity/entity.h>

#include "player_state.h"

#include "player_controller_generated.h"

CLASS(Category = PlayerController)
class PlayerController : public Type
{
public:
	friend class Player;

	PlayerController() = default;
	virtual ~PlayerController() = default;

	virtual void init();
	virtual void update(double deltaTime);
	virtual void possess(Entity* const entity);
	virtual void unposses();

	Entity* const getPossessedEntity() const;
	PlayerState* const getState() const;

	GENERATED_BODY()

protected:
	Entity* m_possessedEntity;
	std::unique_ptr<PlayerState> m_state;
};
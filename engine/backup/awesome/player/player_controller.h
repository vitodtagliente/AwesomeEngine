/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "player_state.h"

#include "player_controller_generated.h"

CLASS(Type = PlayerController)
class PlayerController : public Component
{
public:
	PlayerController() = default;
	virtual ~PlayerController() = default;

	virtual void init() override;
	virtual void possess(class Entity* const entity);
	virtual void unposses();

	inline class Entity* const getPossessedEntity() const { return m_possessedEntity; };
	inline class PlayerState* const getState() const { return m_state;  };
	template <typename T = PlayerState>
	T* const getState() const
	{
		return dynamic_cast<T*>(m_state);
	}

	GENERATED_BODY()

protected:
	class Entity* m_possessedEntity;
	class PlayerState* m_state;
};
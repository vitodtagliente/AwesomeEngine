#pragma once

#include "ecs/component.h"

#include "core/timer.h"
#include "math/vector2.h"

class Bullet : public Component
{
public:
	friend class BulletSystem;

	inline void shoot(const EntityPtr& owner, const math::vec2& direction)
	{
		m_direction = direction;
		m_owner = owner;
	}

	std::size_t damage{ 1 };
	float speed{ 40.f };

private:
	math::vec2 m_direction;
	EntityPtr m_owner;
	Timer m_lifetime{ 10.f };
};
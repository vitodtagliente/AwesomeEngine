#include "pawn.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void Pawn::move(const math::vec3& direction)
{
	const auto delta = direction * speed;
	if (m_body)
	{
		m_body->move(direction * speed);
	}
	
	if (m_animator)
	{
		m_animator->play(delta != math::vec3::zero ? "walk" : "idle", true);
	}

	if (direction.x != 0.0f)
	{
		m_renderer->flipX = direction.x < 0.f;
	}
	if (direction != math::vec3::zero)
	{
		m_direction = direction;
		m_direction.normalize();
	}
}

void Pawn::init()
{
	m_animator = getOwner()->findComponent<SpriteAnimator>();
	m_body = getOwner()->findComponent<Body2d>();
	m_renderer = getOwner()->findComponent<SpriteRenderer>();
}

void Pawn::inspect()
{
	Component::inspect();
	editor::Layout::input("Speed", speed);
}

json::value Pawn::serialize() const
{
	json::value data = Component::serialize();
	data["speed"] = speed;
	return data;
}

void Pawn::deserialize(const json::value& value)
{
	Component::deserialize(value);
	speed = value["speed"].as_number().as_float();
}

REFLECT_COMPONENT(Pawn)
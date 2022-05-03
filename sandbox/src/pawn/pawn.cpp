#include "pawn.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void Pawn::move(const math::vec3& direction)
{
	const auto delta = direction * speed;
	getOwner()->transform.position += (direction * speed);

	if (animator == nullptr)
	{
		animator = getOwner()->findComponent<SpriteAnimator>();
	}

	if (animator)
	{
		animator->play(delta != math::vec3::zero ? "walk" : "idle", true);
	}

	m_direction = direction;
}

void Pawn::init()
{
	animator = getOwner()->findComponent<SpriteAnimator>();
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
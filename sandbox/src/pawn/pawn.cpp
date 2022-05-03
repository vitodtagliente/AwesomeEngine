#include "pawn.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void Pawn::move(const math::vec3& direction)
{
	getOwner()->transform.position += (direction * speed);
	m_direction = direction;
}

void Pawn::inspect()
{
	Component::inspect();
	editor::Layout::input("Speed", speed);
	editor::Layout::input("Direction", m_direction);
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
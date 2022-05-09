#include "pawn.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void Pawn::move(const math::vec3& direction, const double deltaTime)
{
	if (direction != math::vec3::zero)
	{
		m_direction = direction;
		if (m_renderer) m_renderer->flipX = m_direction.x < 0.f;
	}

	if (m_body) m_body->move(direction * speed * static_cast<float>(deltaTime));
	if (m_animator) m_animator->play(direction != math::vec3::zero ? "walk" : "idle", true);
}

void Pawn::dash(const math::vec3& direction, const double deltaTime)
{
	if (m_body == nullptr) return;

	m_body->move(m_direction * dashSpeed * static_cast<float>(deltaTime));
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
	editor::Layout::input("Dash Speed", dashSpeed);
}

json::value Pawn::serialize() const
{
	json::value data = Component::serialize();
	data["speed"] = speed;
	data["dashSpeed"] = dashSpeed;
	return data;
}

void Pawn::deserialize(const json::value& value)
{
	Component::deserialize(value);
	speed = value.safeAt("speed").as_number(1.f).as_float();
	dashSpeed = value.safeAt("dashSpeed").as_number(1.f).as_float();
}

REFLECT_COMPONENT(Pawn)
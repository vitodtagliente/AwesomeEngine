#include "pawn.h"

#include "ecs/entity.h"
#include "ecs/entity_ptr.h"

void Pawn::init()
{
	Entity& e = *entity();
	m_body = e.findComponent<Rigidbody2D>();
	m_health = e.findComponent<Health>();
	m_sprite = e.findComponent<Sprite>();
	m_sprite_animator = e.findComponent<SpriteAnimator>();
}

void Pawn::aim(const math::vec2& direction)
{
	// m_aim_direction = direction;
}

void Pawn::move(const math::vec2& direction)
{
	m_body->velocity = direction * stats.speed;
	if (direction != math::vec2::zero)
	{
		m_sprite->flipX = direction.x < 0.f;
	}
}

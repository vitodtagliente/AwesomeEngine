#include "weapon.h"

#include "game/game_factory.h"

void Weapon::update(double delta_time)
{
	m_timer.tick(delta_time);
}

void Weapon::aim(const math::vec2& direction)
{
	m_direction = direction;
}

void Weapon::attack()
{
	if (!m_timer.isExpired() || m_direction == math::vec2::zero) return;

	Entity& bullet = GameFactory::bullet(entity(), m_direction);
	bullet.transform.position = entity()->transform.position;

	m_timer.reset(1.f);
}

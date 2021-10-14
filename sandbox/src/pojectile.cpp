#include "pojectile.h"

#include <awesome/math/vector3.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

Projectile::Projectile()
	: m_target()
	, m_speed(6.f)
{
}

void Projectile::update(double deltaTime)
{
	if (m_target == nullptr) return;

	math::vec3 direction = m_target->transform.position - getOwner()->transform.position;
	getOwner()->transform.position += direction.normalize() * m_speed * deltaTime;

	if (getOwner()->transform.position.distance(m_target->transform.position) < 0.2f)
	{
		getWorld()->destroy(getOwner());
	}
}

void Projectile::follow(Entity* const target)
{
	m_target = target;
}
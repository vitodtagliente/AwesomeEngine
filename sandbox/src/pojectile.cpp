#include "pojectile.h"

#include <awesome/editor/context.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>
#include <vdtmath/vector3.h>

Projectile::Projectile()
	: m_target()
	, m_speed(6.f)
{
}

void Projectile::update(World& world, double deltaTime)
{
	if (m_target == nullptr) return;

	math::vec3 direction = m_target->transform.position - getOwner()->transform.position;
	getOwner()->transform.position += direction.normalize() * m_speed * deltaTime;

	if (getOwner()->transform.position.distance(m_target->transform.position) < 0.2f)
	{
		world.destroy(getOwner());
	}
}

void Projectile::inspect(editor::Context& context)
{
	context.input("speed", &m_speed);
}

void Projectile::follow(Entity* const target)
{
	m_target = target;
}
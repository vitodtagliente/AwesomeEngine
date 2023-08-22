#include "bullet_system.h"

#include "ecs/entity.h"

void BulletSystem::process(const double delta_time, Bullet& bullet)
{
	bullet.entity()->transform.position += static_cast<float>(delta_time) * bullet.speed;

	bullet.m_lifetime.tick(delta_time);
	if (bullet.m_lifetime.isExpired())
	{
		// bullet.entity()->queue_free();
	}
}
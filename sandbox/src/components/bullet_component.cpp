#include "bullet_component.h"

#include <awesome/component/body2d_component.h>
#include <awesome/component/collider2d_component.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "health_component.h"

void BulletComponent::init()
{
	m_body = getOwner()->findComponent<Body2dComponent>();
	m_collider = getOwner()->findComponent<Collider2dComponent>();
	m_collider->onTrigger.bind([this](const Collider2dComponent& other) -> void
		{
			HealthComponent* health = other.getOwner()->findComponent<HealthComponent>();
			if (health)
			{
				*health -= damage;
				if (m_destroyOnCollision)
				{
					World::instance().destroy(getOwner());
				}
			}
		}
	);
}

void BulletComponent::update(const double deltaTime)
{
	m_body->move(m_direction * speed * static_cast<float>(deltaTime));
}

void BulletComponent::shoot(const math::vec3& direction)
{
	m_direction = direction;
}
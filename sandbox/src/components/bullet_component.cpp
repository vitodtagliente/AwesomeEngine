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
	enabled = m_body != nullptr;
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
	if (m_target != nullptr)
	{
		const auto direction = (m_target->transform.position - getOwner()->transform.position).normalize();
		m_body->move(direction * speed * static_cast<float>(deltaTime));
	}
	else if (m_direction != math::vec3::zero)
	{
		m_body->move(m_direction * speed * static_cast<float>(deltaTime));
	}
}

void BulletComponent::shoot(const math::vec3& direction)
{
	m_direction = direction;
}

void BulletComponent::shoot(Entity* const entity)
{
	m_target = entity;
}
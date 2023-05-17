#include "bullet_component.h"

#include <awesome/components/collider2d_component.h>
#include <awesome/components/rigidbody2d_component.h>
#include <awesome/core/logger.h>
#include <awesome/scene/entity.h>

#include "health_component.h"

void BulletComponent::init()
{
	m_body = getOwner()->findComponent<Rigidbody2DComponent>();
	enabled = m_body != nullptr;
	m_collider = getOwner()->findComponent<Collider2DComponent>();
	if (m_collider)
	{
		m_collider->onTrigger.bind([this](const Collider2DComponent& other) -> void
			{
				if (other.getOwner()->tag != m_targetTag) return;

				HealthComponent* health = other.getOwner()->findComponent<HealthComponent>();
				if (health)
				{
					*health -= damage;
					if (m_destroyOnCollision)
					{
						getOwner()->queue_destroy();
					}
				}
			}
		);
	}
	else
	{
		ERR_LOG("BulletComponent", "Invalid Collider2dComponent, destroying the entity...");
		getOwner()->queue_destroy();
	}
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
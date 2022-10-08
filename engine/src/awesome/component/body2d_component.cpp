#include "body2d_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "collider2d_component.h"

void Body2dComponent::init()
{
	m_collider = getOwner()->findComponent<Collider2dComponent>();
}

void Body2dComponent::move(const math::vec2& amount)
{
	move(math::vec3(amount.x, amount.y, 0.0f));
}

void Body2dComponent::move(const math::vec3& amount)
{
	math::vec3& position = getOwner()->transform.position;
	position += amount;
	if (m_collider)
	{
		const math::vec3 futurePosition = position + amount;
		for (const auto& entity : World::instance().getEntities())
		{
			if (entity->getId() == getOwner()->getId()) continue;

			Collider2dComponent* const collider = entity->findComponent<Collider2dComponent>();
			if (collider && collider->collide(*m_collider))
			{
				position -= amount; // reset the position
				return;
			}
		}
	}
}
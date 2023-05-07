#include "body2d_component.h"

#include <awesome/scene/entity.h>

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
	math::vec3& position = getOwnerTransform().position;
	position += amount;
	if (m_collider)
	{
		// const math::vec3 futurePosition = position + amount;
		// for (const auto& entity : World::instance().findNearestEntities(getOwner()))
		// {
		// 	Collider2dComponent* const collider = entity->findComponent<Collider2dComponent>();
		// 	if (collider && collider->collide(*m_collider))
		// 	{
		// 		if (!m_collider->isTrigger)
		// 		{
		// 			position -= amount; // reset the position
		// 		}
		// 		return;
		// 	}
		// }
	}
}
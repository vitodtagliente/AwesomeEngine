#include "body2d.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "collider2d.h"

void Body2d::init()
{
	m_collider = getOwner()->findComponent<Collider2d>();
}

void Body2d::move(const math::vec2& amount)
{
	move(math::vec3(amount.x, amount.y, 0.0f));
}

void Body2d::move(const math::vec3& amount)
{
	math::vec3& position = getOwner()->transform.position;
	position += amount;
	if (m_collider)
	{
		const math::vec3 futurePosition = position + amount;
		for (const auto& entity : World::instance().getEntities())
		{
			if (entity->getId() == getOwner()->getId()) continue;

			Collider2d* const collider = entity->findComponent<Collider2d>();
			if (collider && collider->collide(*m_collider))
			{
				position -= amount; // reste the position
				return;
			}
		}
	}
}

json::value Body2d::serialize() const
{
	json::value data = Component::serialize();

	return data;
}

void Body2d::deserialize(const json::value& value)
{
	Component::deserialize(value);

}

void Body2d::inspect()
{
	Component::inspect();

}

REFLECT_COMPONENT(Body2d)
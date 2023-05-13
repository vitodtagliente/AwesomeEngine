#include "rigidbody2d_component.h"

#include <awesome/collision/quad_tree.h>
#include <awesome/scene/entity.h>

#include "collider2d_component.h"

void Rigidbody2DComponent::init()
{
	m_collider = getOwner()->findComponent<Collider2DComponent>();
}

void Rigidbody2DComponent::update(const double)
{
	m_direction = (getOwnerTransform().position - m_lastPosition).normalize();
}

void Rigidbody2DComponent::move(const math::vec2& amount)
{
	move(math::vec3(amount.x, amount.y, 0.0f));
}

void Rigidbody2DComponent::move(const math::vec3& amount)
{
	if (m_collider == nullptr) return;

	QuadTree& quadtree = QuadTree::instance();
	math::vec3& position = getOwnerTransform().position;
	const math::vec3 future_position = position + amount;

	const math::rect region = math::rect(future_position.x, future_position.y, m_collider->bounds.x * 2, m_collider->bounds.y * 2);
	for (const auto& entity : quadtree.query(region))
	{
		Collider2DComponent* const other_collider = entity->findComponent<Collider2DComponent>();
		if (other_collider && m_collider->collide(*other_collider))
		{
			if (!m_collider->isTrigger)
			{
				position -= amount; // reset the position
			}
			return;
		}
	}
}
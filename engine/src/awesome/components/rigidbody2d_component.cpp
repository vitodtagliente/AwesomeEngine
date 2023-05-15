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
	if (amount == math::vec3::zero
		|| m_collider == nullptr
		|| m_type != RigidbodyType2D::Kinematic) return;

	math::vec3& position = getOwnerTransform().position;
	const math::vec3 future_position = position + amount;
	const math::vec3 direction = (future_position - position).normalize();

	const math::rect region = math::rect(future_position.x, future_position.y, m_collider->bounds.x * 2, m_collider->bounds.y * 2);

	QuadTree& quadtree = QuadTree::instance();
	for (const auto& entity : quadtree.query(region))
	{
		if (entity->id() == getOwner()->id()) continue;

		Collider2DComponent* const other_collider = entity->findComponent<Collider2DComponent>();
		if (other_collider && m_collider->collideAt(future_position, *other_collider))
		{
			if (!m_collider->isTrigger && !other_collider->isTrigger)
			{
				const math::vec3 future_position_h = position + math::vec3(amount.x, 0.f, 0.f);
				const math::vec3 future_position_v = position + math::vec3(0.f, amount.y, 0.f);
				if (!m_collider->collideAt(future_position_h, *other_collider))
				{
					position = future_position_h;
				}
				if (!m_collider->collideAt(future_position_v, *other_collider))
				{
					position = future_position_v;
				}
				return;
			}
		}
	}
	position = future_position;
}
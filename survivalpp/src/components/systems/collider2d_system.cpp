#include "collider2d_system.h"

#include <cmath>

#include "collision/quad_tree.h"
#include "ecs/entity.h"
#include "math/rectangle.h"

void Collider2DSystem::process(const double delta_time, Collider2D& collider)
{
	math::vec2& position = collider.entity()->transform.position;
	const math::rect region = math::rect(position.x, position.y, collider.shape.bounds.x, collider.shape.bounds.y);
	const float radius = collider.shape.bounds.x * .5f;

	QuadTree& quadtree = QuadTree::instance();
	for (const ComponentPtr<Rigidbody2D>& other : quadtree.query(region))
	{
		if (collider.entity() == other->entity()) continue;

		const float deltaX = position.x - other->entity()->transform.position.x;
		const float deltaY = position.y - other->entity()->transform.position.y;
		if (std::sqrt(deltaX * deltaX + deltaY * deltaY) <= (radius + other->shape.bounds.x * .5f))
		{
			collider.on_collision.invoke(other.get());
		}
	}
}

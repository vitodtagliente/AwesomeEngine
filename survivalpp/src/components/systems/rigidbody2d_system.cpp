#include "rigidbody2d_system.h"

#include <cmath>

#include "collision/quad_tree.h"
#include "ecs/entity.h"
#include "math/rectangle.h"

void Rigidbody2DSystem::process(const double delta_time, Rigidbody2D& body)
{
	if (body.type == RigidbodyType2D::Static
		|| body.velocity == math::vec2::zero) return;

	math::vec2& position = body.entity()->transform.position;
	const math::vec2 future_position = position + body.velocity * static_cast<float>(delta_time);

	const math::rect region = math::rect(future_position.x, future_position.y, body.shape.bounds.x, body.shape.bounds.y);
	const float radius = body.shape.bounds.x * .5f;

	QuadTree& quadtree = QuadTree::instance();
	for (const ComponentPtr<Rigidbody2D>& other : quadtree.query(region))
	{
		if (body.id() == other->id()) continue;

		const float deltaX = future_position.x - other->entity()->transform.position.x;
		const float deltaY = future_position.y - other->entity()->transform.position.y;
		if (std::sqrt(deltaX * deltaX + deltaY * deltaY) <= (radius + other->shape.bounds.x * .5f))
		{
			return;
		}
	}

	position = future_position;
}

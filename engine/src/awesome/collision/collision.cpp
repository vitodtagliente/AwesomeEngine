#include "collision.h"

#include <awesome/components/collider2d_component.h>
#include <awesome/graphics/graphics.h>
#include <awesome/graphics/renderer.h>
#include <awesome/scene/entity.h>

#include "quad_tree.h"

bool Collision::startup()
{
	return true;
}

void Collision::shutdown()
{
}

void Collision::render()
{
	Graphics* const gfx = Graphics::instance();
	if (gfx == nullptr) return;

	QuadTree::instance().render(*gfx->renderer);
}

void Collision::update(const double)
{
	QuadTree& qt = QuadTree::instance();
	qt.clear();

	for (Collider2dComponent* const collider : Collider2dComponent::components())
	{
		Entity* const entity = collider->getOwner();
		if (entity->state() == Entity::State::Alive)
		{
			qt.insert(entity);
		}
	}
}

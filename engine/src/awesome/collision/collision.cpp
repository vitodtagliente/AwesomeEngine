#include "collision.h"

#include <awesome/components/collider2d_component.h>
#include <awesome/engine/engine.h>
#include <awesome/graphics/graphics.h>
#include <awesome/graphics/renderer.h>
#include <awesome/scene/entity.h>

#include "quad_tree.h"

graphics::Renderer* renderer{ nullptr };

Collision::Collision()
	: m_settings(Engine::instance().settings)
{
}

bool Collision::startup()
{
	Graphics* const gfx = Graphics::instance();
	if (gfx != nullptr)
	{
		renderer = gfx->renderer.get();
	}
	return true;
}

void Collision::shutdown()
{
}

void Collision::render()
{
	if (renderer == nullptr)
	{
		Graphics* const gfx = Graphics::instance();
		if (gfx == nullptr) return;
		renderer = gfx->renderer.get();
		if (renderer == nullptr) return;
	}

	if (m_settings.mode == EngineMode::Editor
		&& m_settings.renderingSettings.renderQuadtree)
	{
		QuadTree::instance().render(*renderer, m_settings.renderingSettings.quadtreeWireColor);
	}
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

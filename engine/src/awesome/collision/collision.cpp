#include "collision.h"

#include <awesome/components/collider2d_component.h>
#include <awesome/engine/engine.h>
#include <awesome/graphics/graphics_pipeline.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

#include "quad_tree.h"

graphics::Renderer* renderer{ nullptr };

Collision::Collision()
	: m_settings(Engine::instance().settings.renderer)
{
}

bool Collision::startup()
{
	GraphicsPipeline* const gfx = GraphicsPipeline::instance();
	if (gfx != nullptr)
	{
		renderer = gfx->renderer(GraphicsPipeline::RenderStage::Name::Scene);
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
		GraphicsPipeline* const gfx = GraphicsPipeline::instance();
		if (gfx == nullptr) return;
		renderer = gfx->renderer(GraphicsPipeline::RenderStage::Name::Scene);
		if (renderer == nullptr) return;
	}

	if (m_settings.debug && m_settings.renderQuadtree)
	{
		QuadTree::instance().render(*renderer, m_settings.quadtreeWireColor);
	}
}

void Collision::update(const double)
{
	QuadTree& qt = QuadTree::instance();
	qt.clear();

	for (Collider2DComponent* const collider : SceneGraph::instance().root().findComponentsInChildren<Collider2DComponent>())
	{
		Entity* const entity = collider->getOwner();
		if (entity->state() == Entity::State::Alive)
		{
			qt.insert(entity);
		}
	}
}

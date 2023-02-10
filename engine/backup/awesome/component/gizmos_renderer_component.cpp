#include "gizmos_renderer_component.h"

#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

void GizmosRendererComponent::render(graphics::Renderer* const renderer)
{
	switch (type)
	{
	case ShapeType::Circle: renderer->submitDrawCircle(graphics::ShapeRenderStyle::stroke, getOwner()->transform.position, std::max(getOwner()->transform.scale.x, getOwner()->transform.scale.y), color); break;
	case ShapeType::Rect: renderer->submitDrawRect(graphics::ShapeRenderStyle::stroke, getOwner()->transform.position, getOwner()->transform.scale.x, getOwner()->transform.scale.y, color); break;
	default: break;
	}
}
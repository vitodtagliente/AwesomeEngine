#include "gizmos_renderer_component.h"

#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

void GizmosRendererComponent::render(graphics::Renderer2D* const renderer)
{
	renderer->setPolygonStyle(graphics::PolygonStyle::stroke);
	switch (type)
	{
	case Type::Rect: renderer->drawRect(getOwner()->transform.position, getOwner()->transform.scale.x, getOwner()->transform.scale.y, color); break;
	case Type::Circle: renderer->drawCircle(getOwner()->transform.position, std::max(getOwner()->transform.scale.x, getOwner()->transform.scale.y), color); break;
	default: break;
	}
	renderer->setPolygonStyle(graphics::PolygonStyle::fill);
}
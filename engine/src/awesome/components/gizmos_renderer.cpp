#include "gizmos_renderer.h"

#include <awesome/scene/entity.h>
#include <awesome/graphics/renderer.h>

GizmosRenderer::GizmosRenderer()
	: Component()
	, type(Type::None)
	, color(Color::White)
{

}

void GizmosRenderer::render(Renderer& renderer)
{
	switch (type)
	{
	case Type::Rect: renderer.getGizmos().rect(getOwner()->transform.position, getOwner()->transform.scale.x, getOwner()->transform.scale.y, color); break;
	case Type::Circle: renderer.getGizmos().circle(getOwner()->transform.position, std::max(getOwner()->transform.scale.x, getOwner()->transform.scale.y), color); break;
	default: break;
	}
}
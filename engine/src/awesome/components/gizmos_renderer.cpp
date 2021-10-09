#include "gizmos_renderer.h"

#include <awesome/scene/entity.h>
#include <awesome/graphics/renderer.h>

GizmosRenderer::GizmosRenderer()
	: Component()
	, type(Type::None)
	, size(1.0f)
	, color(Color::White)
{

}

void GizmosRenderer::render(Renderer& renderer)
{
	switch (type)
	{
	case Type::Rect: renderer.getGizmos().rect(getOwner()->transform.position, size, size, color); break;
	case Type::Circle: renderer.getGizmos().circle(getOwner()->transform.position, size, color); break;
	default: break;
	}
}
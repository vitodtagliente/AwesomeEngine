#include "gizmos_renderer.h"

#include <awesome/editor/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/scene/entity.h>

GizmosRenderer::GizmosRenderer()
	: Component()
	, type(Type::None)
	, color(graphics::Color::White)
{

}

void GizmosRenderer::render(graphics::Renderer& renderer)
{
	switch (type)
	{
	case Type::Rect: renderer.getGizmos().rect(getOwner()->transform.position, getOwner()->transform.scale.x, getOwner()->transform.scale.y, color); break;
	case Type::Circle: renderer.getGizmos().circle(getOwner()->transform.position, std::max(getOwner()->transform.scale.x, getOwner()->transform.scale.y), color); break;
	default: break;
	}
}

void GizmosRenderer::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("color", &color);
}

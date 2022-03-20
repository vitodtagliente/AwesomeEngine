#include "gizmos_renderer.h"

#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

GizmosRenderer::GizmosRenderer()
	: Component()
	, type(Type::None)
	, color(graphics::Color::White)
{

}

void GizmosRenderer::render(graphics::Renderer* const renderer)
{
	switch (type)
	{
	case Type::Rect: renderer->getGizmos().rect(getOwner()->transform.position, getOwner()->transform.scale.x, getOwner()->transform.scale.y, color); break;
	case Type::Circle: renderer->getGizmos().circle(getOwner()->transform.position, std::max(getOwner()->transform.scale.x, getOwner()->transform.scale.y), color); break;
	default: break;
	}
}

json::value GizmosRenderer::serialize() const
{
	json::value data = Component::serialize();
	data.insert("type", static_cast<int>(type));
	data.insert("color", ::serialize(color));
	return data;
}

void GizmosRenderer::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("Color", &color);
}

REFLECT_IMP(GizmosRenderer)
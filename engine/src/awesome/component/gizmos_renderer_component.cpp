#include "gizmos_renderer_component.h"

#include <awesome/editor/layout.h>
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

json::value GizmosRendererComponent::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = static_cast<int>(type);
	data["color"] = ::serialize(color);
	return data;
}

void GizmosRendererComponent::deserialize(const json::value& value)
{
	Component::deserialize(value);
	type = static_cast<Type>(value["type"].as_number(static_cast<int>(Type::None)).as_int());
	::deserialize(value["color"], color);
}

void GizmosRendererComponent::inspect()
{
	Component::inspect();
	Layout::input("Type", type, { {"None", Type::None}, {"Rect", Type::Rect}, {"Circle", Type::Circle} });
	Layout::input("Color", color);
}
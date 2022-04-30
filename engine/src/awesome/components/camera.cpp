#include "camera.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>

void Camera::render(graphics::Renderer* const renderer)
{
	renderer->backgroundColor = color;
}

json::value Camera::serialize() const
{
	json::value data = Component::serialize();
	data["color"] = ::serialize(color);
	return data;
}

void Camera::deserialize(const json::value& value)
{
	Component::deserialize(value);
	::deserialize(value["color"].as_object({}), color);
}

void Camera::inspect()
{
	Component::inspect();
	editor::Layout::input("Color", color);
}

REFLECT_COMPONENT(Camera)
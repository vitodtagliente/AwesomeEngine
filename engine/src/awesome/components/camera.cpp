#include "camera.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>

void Camera::update(double)
{
	auto& renderer = graphics::Renderer::instance();
	renderer.backgroundColor = color;
	renderer.setView(getOwner()->transform.matrix());
}

math::vec3 Camera::screenToWorldCoords(const math::vec2& point)
{
	auto& renderer = graphics::Renderer::instance();
	bool isInvertible = false;
	const auto r = renderer.getViewProjectionMatrix().inverse(isInvertible) * math::vec4(point.x, point.y, 0.f, 0.f);
	return math::vec3(r.x, r.y, r.z);
}

Camera* const Camera::main()
{
	World& world = World::instance();
	for (const auto& entity : world.getEntities())
	{
		Camera* const camera = entity->findComponent<Camera>();
		if (camera) return camera;
	}
	return nullptr;
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
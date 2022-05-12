#include "camera.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>

void Camera::update(double)
{
	auto& renderer = graphics::Renderer::instance();
	renderer.backgroundColor = color;
	renderer.setProjection(computeProjectionMatrix());
	renderer.setView(getOwner()->transform.matrix());
}

math::vec3 Camera::screenToWorldCoords(const math::vec2& point)
{
	auto& renderer = graphics::Renderer::instance(); 
	Canvas& canvas = Canvas::instance();
	bool isInvertible = false;

	math::vec4 normalizedScreenPosition(
		2.f * (point.x / static_cast<float>(canvas.getWidth())) - 1.f - getOwner()->transform.position.x,
		2.f * (-point.y / static_cast<float>(canvas.getHeight())) + 1.f - getOwner()->transform.position.y,
		0.f,
		0.f
	);
	const auto r = renderer.getViewProjectionMatrix().inverse(isInvertible) * normalizedScreenPosition;
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

math::matrix4 Camera::computeProjectionMatrix()
{
	return math::matrix4::identity;
}

REFLECT_COMPONENT(Camera)
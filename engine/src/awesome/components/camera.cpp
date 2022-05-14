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
	bool invertible = false;
	renderer.setView(getOwner()->transform.matrix().inverse(invertible));
}

math::vec3 Camera::screenToWorldCoords(const math::vec2& point)
{
	auto& renderer = graphics::Renderer::instance();
	Canvas& canvas = Canvas::instance();
	bool isInvertible = false;

	// math::vec4 normalizedScreenPosition(
	// 	2.f * (point.x / static_cast<float>(canvas.getWidth())) - 1.f - getOwner()->transform.position.x,
	// 	2.f * (-point.y / static_cast<float>(canvas.getHeight())) + 1.f - getOwner()->transform.position.y,
	// 	0.f,
	// 	0.f
	// );
	// const auto r = renderer.getViewProjectionMatrix().inverse(isInvertible) * normalizedScreenPosition;
	// return math::vec3(r.x, r.y, r.z);
	math::vec4 normalizedScreenPosition(
		((float)point.x / (float)canvas.getWidth() - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		-((float)point.y / (float)canvas.getHeight() - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		0.f, // The near plane maps to Z=-1 in Normalized Device Coordinates
		0.f
	);

	// Faster way (just one inverse)
	math::mat4 M = renderer.getViewProjectionMatrix().inverse(isInvertible);
	math::vec4 r = M * normalizedScreenPosition;

	return math::vec3(r.x, r.y, 0.f);
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
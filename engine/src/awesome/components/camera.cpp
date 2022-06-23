#include "camera.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>

void Camera::update(double)
{
	auto& renderer = graphics::Context::instance().renderer;
	renderer.setClearColor(color);
	renderer.setProjectionMatrix(computeProjectionMatrix());
	renderer.setViewMatrix(getOwner()->transform.matrix());
}

math::vec3 Camera::screenToWorldCoords(const math::vec2& point)
{
	auto& renderer = graphics::Context::instance().renderer;
	return renderer.screenToWorldCoords(point);
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
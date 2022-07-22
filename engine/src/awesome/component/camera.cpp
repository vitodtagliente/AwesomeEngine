#include "camera.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>

namespace component
{
	Camera::Camera()
		: m_data(std::make_unique<graphics::Camera>())
	{
	}

	void Camera::update(double)
	{
		auto& renderer = graphics::Context::instance().renderer;
		const auto& canvas = Canvas::instance();
		renderer.setClearColor(color);
		renderer.setViewport(canvas.getWidth(), canvas.getHeight());

		renderer.setProjectionMatrix(m_data->getProjectionMatrix(canvas.getWidth(), canvas.getHeight()));
		m_data->transform = getOwner()->transform;
		m_data->transform.position.x = -m_data->transform.position.x;
		m_data->transform.position.y = -m_data->transform.position.y;
		m_data->update();
		renderer.setViewMatrix(m_data->getViewMatrix());
	}

	math::vec3 Camera::screenToWorldCoords(const math::vec2& point)
	{
		const auto& canvas = Canvas::instance();
		return m_data->screenToWorldCoords(point, canvas.getWidth(), canvas.getHeight());
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
}
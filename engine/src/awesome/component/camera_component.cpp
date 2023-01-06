#include "camera_component.h"

#include <awesome/application/canvas.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

CameraComponent::CameraComponent()
	: m_data(std::make_unique<graphics::Camera>())
{
}

void CameraComponent::update(double)
{
	m_data->transform = getOwner()->transform;
	m_data->transform.position.x = -m_data->transform.position.x;
	m_data->transform.position.y = -m_data->transform.position.y;
	m_data->update();
}

math::vec3 CameraComponent::screenToWorldCoords(const math::vec2& point)
{
	const auto& canvas = Canvas::instance();
	return m_data->screenToWorldCoords(point, canvas.getWidth(), canvas.getHeight());
}

CameraComponent* const CameraComponent::main()
{
	return World::instance().findComponentInChildren<CameraComponent>();
}
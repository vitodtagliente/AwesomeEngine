#include "camera_component.h"

#include <awesome/engine/canvas.h>
#include <awesome/graphics/camera.h>
#include <awesome/graphics/graphics_pipeline.h>

CameraComponent* CameraComponent::s_instance{ nullptr };

void CameraComponent::init()
{
	s_instance = this;
	m_renderer = GraphicsPipeline::instance()->sceneRenderer.get();
}

void CameraComponent::update(const double)
{
	// apply only if this is the main camera
	if (this != s_instance) return;

	m_renderer->setViewMatrix(getOwnerTransform().matrix());
	m_renderer->setProjectionMatrix(computeProjectionMatrix());
}

math::vec3 CameraComponent::screenToWorldCoords(const math::vec2& point)
{
	const auto& canvas = Canvas::instance();
	const math::vec2 screenSize{ static_cast<float>(canvas.getWidth()) , static_cast<float>(canvas.getHeight()) };

	const math::vec4 viewport{ 0, 0, screenSize.x, screenSize.y };
	const math::vec3 screencoords{ point.x, screenSize.y - point.y - 1, 0.0f };
	return math::mat4::unproject(screencoords, m_renderer->getViewMatrix(), m_renderer->getProjectionMatrix(), viewport);
}

CameraComponent* const CameraComponent::main()
{
	return s_instance;
}

math::mat4 CameraComponent::computeProjectionMatrix() const
{
	return graphics::Camera::view(getOwnerTransform());
}

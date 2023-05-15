#include "camera_follow2d_component.h"

#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

#include "orthographic_camera_component.h"

void CameraFollow2dComponent::init()
{
	m_ortho = getOwner()->findComponent<OrthographicCameraComponent>();
}

void CameraFollow2dComponent::update(const double deltaTime)
{
	if (m_target == nullptr)
	{
		if (m_targetTag.empty()) return;

		m_target = SceneGraph::instance().root().findChildByTag(m_targetTag);
		if (m_target == nullptr) return;
	}

	math::vec3& current_position = getOwnerTransform().position;
	math::vec3 desired_position = m_target->transform.position;
	if (m_ortho && m_ortho->pixelPerfect)
	{
		desired_position.x /= static_cast<float>(m_ortho->pixelsPerUnit);
		desired_position.y /= static_cast<float>(m_ortho->pixelsPerUnit / 2);
	}

	current_position = math::vec3(
		math::lerp(current_position.x, -desired_position.x, m_speed * static_cast<float>(deltaTime)),
		math::lerp(current_position.y, -desired_position.y, m_speed * static_cast<float>(deltaTime)),
		desired_position.z
	);
}
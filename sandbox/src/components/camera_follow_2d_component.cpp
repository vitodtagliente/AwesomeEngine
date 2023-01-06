#include "camera_follow_2d_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

void CameraFollow2dComponent::update(const double deltaTime)
{
	if (m_target == nullptr)
	{
		const auto& entities = World::instance().findChildrenByTag("Player");
		if (!entities.empty())
		{
			m_target = entities.front();
		}
	}

	if (m_target)
	{
		math::vec3& position = getOwner()->transform.position;
		const math::vec3& desiredPosition = m_target->transform.position;

		position = math::vec3(
			math::lerp(position.x, -desiredPosition.x / 32, m_speed * static_cast<float>(deltaTime)),
			math::lerp(position.y, -desiredPosition.y / 16, m_speed * static_cast<float>(deltaTime)),
			desiredPosition.z
		);
	}
}
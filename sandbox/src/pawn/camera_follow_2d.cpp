#include "camera_follow_2d.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

void CameraFollow2d::update(const double deltaTime)
{
	if (m_target == nullptr)
	{
		const auto& entities = World::instance().findEntitiesByTag("Player");
		if (!entities.empty())
		{
			m_target = entities.front();
		}
	}

	if (m_target)
	{
		math::vec3& position = getOwner()->transform.position;
		const math::vec3& desiredPosition = m_target->transform.position / 32;

		position = math::vec3(
			math::lerp(position.x, -desiredPosition.x, m_speed * static_cast<float>(deltaTime)),
			math::lerp(position.y, -desiredPosition.y, m_speed * static_cast<float>(deltaTime)),
			desiredPosition.z
		);
	}
}

void CameraFollow2d::inspect()
{
	Component::inspect();
	editor::Layout::input("Speed", m_speed);
}

json::value CameraFollow2d::serialize() const
{
	json::value data = Component::serialize();
	data["speed"] = m_speed;
	return data;
}

void CameraFollow2d::deserialize(const json::value& data)
{
	Component::deserialize(data);
	m_speed = data.safeAt("speed").as_number(1.0f).as_float();
}

REFLECT_COMPONENT(CameraFollow2d)
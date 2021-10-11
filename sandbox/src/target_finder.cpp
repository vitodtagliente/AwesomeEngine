#include "target_finder.h"

#include <vector>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

TargetFinder::TargetFinder(const float radius, const Mode mode)
	: m_mode(mode)
	, m_target(nullptr)
	, m_radius(radius)
{
}

Entity* const TargetFinder::getTarget() const
{
	return m_target;
}

bool TargetFinder::hasTarget() const
{
	return m_target != nullptr;
}

void TargetFinder::check(World& world, const math::vec3& position)
{
	switch (m_mode)
	{
	case Mode::Closer:
	{
		m_target = findTheClosest(world, position);
		break;
	}
	case Mode::FIFO:
	{
		if (m_target != nullptr)
		{
			const float distance = position.distance(m_target->transform.position);
			if (distance < m_radius) return;
		}
		m_target = findTheClosest(world, position);
		break;
	}
	default: break;
	}
}

Entity* const TargetFinder::findTheClosest(World& world, const math::vec3& position)
{
	std::vector<Entity*> minions = world.getEntitiesByTag("minion");
	if (minions.empty()) return nullptr;

	Entity* closestTarget = nullptr;
	float closestDistance = m_radius;
	for (auto it = minions.begin(); it != minions.end(); ++it)
	{
		Entity* const entity = *it;
		const float distance = position.distance(entity->transform.position);
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestTarget = entity;
		}
	}
	return closestTarget;
}
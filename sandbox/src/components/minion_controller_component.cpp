#include "minion_controller_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/math/vector3.h>

#include "pawn_component.h"

void MinionControllerComponent::init()
{
	getOwner()->tag = "Minion";
	m_pawn = getOwner()->findComponent<PawnComponent>();
}

void MinionControllerComponent::update(const double deltaTime)
{
	if (findTarget())
	{
		const auto direction = (m_target->transform.position - getOwner()->transform.position).normalize();
		if (m_pawn) m_pawn->move(direction, deltaTime);
	}
	else
	{
		World::instance().destroy(getOwner());
	}
}

bool MinionControllerComponent::findTarget()
{
	if (m_target) return true;

	m_target = World::instance().findEntityByTag(m_targetTag);
	return m_target != nullptr;
}

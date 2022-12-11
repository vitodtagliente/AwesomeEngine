#include "shoot_component.h"

#include <awesome/entity/entity.h>

#include "aim_component.h"

void ShootComponent::init()
{
	m_aim = getOwner()->findComponent<AimComponent>();
}

void ShootComponent::update(const double deltaTime)
{
	
}

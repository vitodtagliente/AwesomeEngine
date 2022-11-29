#include "healer_component.h"

#include <awesome/entity/entity.h>
#include "../health_component.h"

void HealerComponent::init()
{
	WeaponComponent::init();
	m_health = getOwner()->findComponent<HealthComponent>();
}

void HealerComponent::update(const double deltaTime)
{
	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		if (m_health)
		{
			(*m_health) += static_cast<int>(efficacy);
		}
		m_activationTimer = frequency;
	}
}

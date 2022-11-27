#include "healer_component.h"

#include <awesome/entity/entity.h>
#include "../health_component.h"

void HealerComponent::init()
{
	m_health = getOwner()->findComponent<HealthComponent>();
	m_activationTimer = frequency;
}

void HealerComponent::update(const double deltaTime)
{
	if (m_health == nullptr)
	{
		return;
	}

	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		(*m_health) += efficacy;
		m_activationTimer = frequency;
	}
}

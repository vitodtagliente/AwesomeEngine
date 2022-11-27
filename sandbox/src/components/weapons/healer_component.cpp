#include "healer_component.h"

#include <awesome/entity/entity.h>
#include "../health_component.h"

void HealerComponent::init()
{
	m_health = getOwner()->findComponent<HealthComponent>();
	enabled = m_health != nullptr;
	m_activationTimer = frequency;
}

void HealerComponent::update(const double deltaTime)
{
	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		(*m_health) += efficacy;
		m_activationTimer = frequency;
	}
}

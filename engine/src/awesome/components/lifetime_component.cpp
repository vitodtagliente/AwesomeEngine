#include "lifetime_component.h"

void LifetimeComponent::init()
{
	m_timer = lifetime;
}

void LifetimeComponent::update(const double deltaTime)
{
	m_timer -= deltaTime;
	if (m_timer <= 0.0)
	{
		queueOwnerDestroy();
	}
}
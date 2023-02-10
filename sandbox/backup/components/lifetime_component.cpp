#include "lifetime_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

void LifetimeComponent::init()
{
	m_timer = value;
}

void LifetimeComponent::update(double deltaTime)
{
	if (m_timer > 0.0)
	{
		m_timer -= deltaTime;
		if (m_timer <= 0.0)
		{
			getOwner()->queue_destroy();
		}
	}
}
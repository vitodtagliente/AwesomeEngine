#include "lifetime_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

void LifetimeComponent::update(double deltaTime)
{
	m_timer -= deltaTime;
	if (m_timer <= 0.0)
	{
		World::instance().destroy(getOwner());
	}
}

void LifetimeComponent::inspect()
{
	Component::inspect();
	editor::Layout::input("Destroy after", m_lifetime);
}

json::value LifetimeComponent::serialize() const
{
	json::value data = Component::serialize();
	data["value"] = m_lifetime;
	return data;
}

void LifetimeComponent::deserialize(const json::value& data)
{
	Component::deserialize(data);
	m_timer = m_lifetime = data.safeAt("value").as_number(1.0).as_double();
}
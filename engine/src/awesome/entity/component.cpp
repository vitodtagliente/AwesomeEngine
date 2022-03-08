#include "component.h"

#include <awesome/editor/context.h>
#include <awesome/graphics/renderer.h>

#include "entity.h"
#include "world.h"

Component::Component()
	: enabled(true)
	, m_owner()
{
}

World* const Component::getWorld() const
{
	return m_owner ? m_owner->getWorld() : nullptr;
}

void Component::attach(Entity* const entity)
{
	m_owner = entity;
	init();
}

void Component::detach()
{
	uninit();
	m_owner = nullptr;
}

json::value Component::toJson() const
{
	return json::value();
}

void Component::fromJson(const json::value& data)
{
}

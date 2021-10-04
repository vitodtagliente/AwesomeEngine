#include "component.h"

#include "entity.h"
#include "world.h"

Component::Component()
	: enabled(true)
	, m_owner()
{
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

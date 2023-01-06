#include "component.h"

#include <awesome/core/serialization.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

Component::Component()
	: Type()
{
}

bool Component::operator==(const Component& other) const
{
	return m_id == other.m_id;
}

bool Component::operator!=(const Component& other) const
{
	return m_id != other.m_id;
}

void Component::attach(Entity* const entity)
{
	m_owner = entity;
}

void Component::detach()
{
	uninit();
	m_owner = nullptr;
}

void Component::inspect()
{
	Layout::input(*this);
}
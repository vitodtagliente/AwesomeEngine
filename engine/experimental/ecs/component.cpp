#include "component.h"

#include "entity.h"

bool Component::operator==(const Component& other) const
{
	return m_id == other.m_id;
}

bool Component::operator!=(const Component& other) const
{
	return m_id != other.m_id;
}

void Component::attach(const EntityPtr& entity)
{
	m_entity = entity;
}

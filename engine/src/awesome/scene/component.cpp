#include "component.h"

#include <awesome/scene/entity.h>

Component::Component(const Component& other)
	: enabled(other.enabled)
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
}

json::value Component::serialize() const
{
	return json::value();
}

bool Component::deserialize(const json::value&)
{
	return true;
}

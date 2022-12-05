#include "component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

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

json::value Component::serialize() const
{
	json::value data = Serializer::serialize(*this);
	data["component_type"] = this->getTypeName();
	return data;
}

void Component::deserialize(const json::value& value)
{
	Deserializer::deserialize(value, *this);
}

void Component::inspect()
{
	Layout::input(*this);
}
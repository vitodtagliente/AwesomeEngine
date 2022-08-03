#include "component.h"

#include <awesome/editor/layout.h>

#include "entity.h"

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
	return json::object({
		{"componentclass", get_descriptor().name},
		{"id", static_cast<std::string>(m_id)},
		{"enabled", enabled},
		{"netMode", enumToString(m_netMode)}
		});
}

void Component::deserialize(const json::value& value)
{
	::deserialize(value.safeAt("id"), m_id);
	enabled = value.safeAt("enabled").as_bool(false);
	stringToEnum(value.safeAt("netMode").as_string(""), m_netMode);
}

void Component::inspect()
{
	editor::Layout::input("Enabled", enabled);
	editor::Layout::input("Net Mode", m_netMode);
}
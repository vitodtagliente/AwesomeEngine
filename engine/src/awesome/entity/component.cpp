#include "component.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>

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
		{"componentclass", getTypeDescriptor().name},
		{"id", static_cast<std::string>(m_id)},
		{"enabled", enabled}
		});
}

void Component::deserialize(const json::value& value)
{
	::deserialize(value["id"], m_id);
	enabled = value["enabled"].as_bool(false);
}

void Component::inspect()
{
	editor::Layout::input("Enabled", enabled);
}

REFLECT_IMP(Component)
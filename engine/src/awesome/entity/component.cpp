#include "component.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>

#include "entity.h"
#include "world.h"

Component::Component()
	: enabled(true)
	, m_id()
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

}

void Component::inspect()
{
	editor::Layout::input("Enabled", enabled);
}

REFLECT_IMP(Component)
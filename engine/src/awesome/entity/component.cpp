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

void Component::inspect(editor::Context& context)
{
	context.input("enabled", &enabled);
}

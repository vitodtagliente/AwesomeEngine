#include "entity.h"
#include "world.h"

#include <awesome/graphics/renderer.h>

void Entity::prepareToSpawn(World& world)
{
}

void Entity::prepareToDestroy()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* const component = *it;
		component->uninit();
		delete component;
	}
	m_components.clear();
}

void Entity::setParent(Entity* const entity)
{
	m_parent = entity;
}

void Entity::update(World& world, double deltaTime)
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* const component = *it;
		if (!component->enabled) continue;

		component->update(world, deltaTime);
	}

	transform.update();
}

void Entity::render(graphics::Renderer& renderer)
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* const component = *it;
		if (!component->enabled) continue;

		component->render(renderer);
	}
}

void Entity::removeComponent(Component* const component)
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		if (*it == component)
		{
			component->detach();
			m_components.erase(it);
			delete component;
			return;
		}
	}
}

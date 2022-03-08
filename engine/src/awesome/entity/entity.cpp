#include "entity.h"

#include <awesome/graphics/renderer.h>

#include "world.h"

Entity::Entity(World* const world)
	: name()
	, tag()
	, transform()
	, m_id()
	, m_world(world)
	, m_parent(nullptr)
	, m_children()
	, m_components()
{

}

Entity::~Entity()
{

}

void Entity::prepareToSpawn()
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

	// destroy the children
	// TODO
}

void Entity::setParent(Entity* const entity)
{
	m_parent = entity;
}

void Entity::update(const double deltaTime)
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* const component = *it;
		if (!component->enabled) continue;

		component->update(deltaTime);
	}

	transform.update();
}

void Entity::render(graphics::Renderer* const renderer)
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

json::value Entity::toJson() const
{
	json::value data = json::object();
	data.insert("name", name);
	data.insert("tag", tag);
	return data;
}

void Entity::fromJson(const json::value& data)
{
}

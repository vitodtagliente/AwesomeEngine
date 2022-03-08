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
	static const auto& entitiesToJson = [](const std::vector<Entity*>& entities) -> json::value
	{
		json::value data = json::array();
		for (const Entity* entity : entities)
		{
			data.push_back(entity->toJson());
		}
		return data;
	};

	static const auto& componentsToJson = [](const std::vector<Component*>& components) -> json::value
	{
		json::value data = json::array();
		for (const Component* component : components)
		{
			data.push_back(component->toJson());
		}
		return data;
	};

	static const auto& transformToJson = [](const math::transform& t) -> json::value
	{
		return json::object({
			{"position", json::object({ {"x", t.position.x}, {"y", t.position.y}, {"z", t.position.z} })},
			{"rotation", json::object({ {"x", t.rotation.x}, {"y", t.rotation.y}, {"z", t.rotation.z} })},
			{"scale", json::object({ {"x", t.scale.x}, {"y", t.scale.y}, {"z", t.scale.z} })},
			});
	};

	return json::object({
		{"id", m_id.toString()},
		{"name", name},
		{"tag", tag},
		{"transform", transformToJson(transform)},
		{"children", entitiesToJson(m_children)},
		{"components", componentsToJson(m_components)}
		});
}

void Entity::fromJson(const json::value& data)
{
}

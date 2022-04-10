#include "entity.h"

#include <awesome/graphics/renderer.h>

#include "world.h"

Entity::Entity()
	: name()
	, tag()
	, transform()
	, m_id()
	, m_world(nullptr)
	, m_parent(nullptr)
	, m_children()
	, m_components()
{

}

Entity::~Entity()
{

}

void Entity::prepareToSpawn(World* const world)
{
	m_world = world;
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

json::value Entity::serialize() const
{
	static const auto& entitiesToJson = [](const std::vector<Entity*>& entities) -> json::value
	{
		json::value data = json::array();
		for (const Entity* entity : entities)
		{
			data.push_back(entity->serialize());
		}
		return data;
	};

	static const auto& componentsToJson = [](const std::vector<Component*>& components) -> json::value
	{
		json::value data = json::array();
		for (const Component* component : components)
		{
			data.push_back(component->serialize());
		}
		return data;
	};

	return json::object({
		{"id", ::serialize(m_id)},
		{"name", name},
		{"tag", tag},
		{"transform", ::serialize(transform)},
		{"children", entitiesToJson(m_children)},
		{"components", componentsToJson(m_components)}
		});
}

void Entity::deserialize(const json::value& value)
{
	if (!value.is_object())
		return;

	name = value["name"].as_string();
	tag = value["tag"].as_string();
	::deserialize(value["transform"], transform);

	const json::value::array_t& components = value["components"].as_array();
	for (const json::value& data : components)
	{
		const std::string& type = data["componentclass"].as_string();
		Component* const component = addComponent(TypeFactory::instantiate<Component>(type));
		component->deserialize(data);
	}
}

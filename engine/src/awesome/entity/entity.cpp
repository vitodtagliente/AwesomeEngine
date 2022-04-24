#include "entity.h"

#include <awesome/graphics/renderer.h>
#include <awesome/entity/world.h>

void Entity::prepareToSpawn(World* const world)
{
	m_world = world;
}

void Entity::prepareToDestroy()
{
	for (const auto& component : m_components)
	{
		component->uninit();
	}
	m_components.clear();

	for (const auto& child : m_children)
	{
		child->prepareToDestroy();
	}
	m_children.clear();
}

void Entity::setParent(Entity* const entity)
{
	m_parent = entity;
}

void Entity::update(const double deltaTime)
{
	for (const auto& component : m_components)
	{
		if (component->enabled)
		{
			component->update(deltaTime);
		}
	}
	transform.update();
}

void Entity::duplicate(const Entity& from, Entity& duplicate)
{
	const uuid id = duplicate.m_id;
	duplicate.deserialize(from.serialize());
	duplicate.m_id = id;
}

void Entity::duplicate(const PrefabAssetPtr& prefab, Entity& duplicate)
{
	const uuid id = duplicate.m_id;
	duplicate.deserialize(json::Deserializer::parse(prefab->data));
	duplicate.m_id = id;
	duplicate.m_prefab = prefab->id;
}

void Entity::render(graphics::Renderer* const renderer)
{
	for (const auto& component : m_components)
	{
		if (component->enabled)
		{
			component->render(renderer);
		}
	}
}

bool Entity::operator==(const Entity& other) const
{
	return m_id == other.m_id;
}

bool Entity::operator!=(const Entity& other) const
{
	return m_id != other.m_id;
}

void Entity::removeComponent(Component* const component)
{
	removeComponent(component->getId());
}

void Entity::removeComponent(const uuid& id)
{
	const auto& it = std::find_if(m_components.begin(), m_components.end(), [&id](const std::unique_ptr<Component>& component) -> bool
		{
			return component->getId() == id;
		}
	);

	if (it != m_components.end())
	{
		(*it)->detach();
		m_components.erase(it);
	}
}

json::value Entity::serialize() const
{
	static const auto& entitiesToJson = [](const std::vector<std::unique_ptr<Entity>>& entities) -> json::value
	{
		json::value data = json::array();
		for (const auto& entity : entities)
		{
			data.push_back(entity->serialize());
		}
		return data;
	};

	static const auto& componentsToJson = [](const std::vector<std::unique_ptr<Component>>& components) -> json::value
	{
		json::value data = json::array();
		for (const auto& component : components)
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

	::deserialize(value["id"], m_id);
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

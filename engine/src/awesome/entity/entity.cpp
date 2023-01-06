#include "entity.h"

#include <awesome/core/serialization.h>

void Entity::prepareToSpawn()
{
	for (const auto& component : m_components)
	{
		component->init();
	}

	m_state = State::Alive;
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

	m_state = State::PendingDestroy;
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

Entity* const Entity::instantiate(const PrefabAssetPtr& prefab)
{
	Entity* const entity = new Entity();
	if (prefab != nullptr && prefab->state == Asset::State::Ready)
	{
		entity->deserialize(prefab->data.value());
		entity->m_prefab = prefab->descriptor.id;
		entity->m_id = uuid();
	}
	return entity;
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
		{"id", Serializer::serialize(m_id)},
		{"name", name},
		{"replicate", replicate},
		{"tag", tag},
		{"transform", Serializer::serialize(transform)},
		{"children", entitiesToJson(m_children)},
		{"components", componentsToJson(m_components)}
		});
}

void Entity::deserialize(const json::value& value)
{
	if (!value.is_object())
		return;

	m_children.clear();
	m_components.clear();

	Deserializer::deserialize(value.safeAt("id"), m_id);
	replicate = value.safeAt("replicate").as_bool(false);
	name = value.safeAt("name").as_string("");
	tag = value.safeAt("tag").as_string("");
	Deserializer::deserialize(value.safeAt("transform"), transform);

	const json::value::array_t& components = value.safeAt("components").as_array();
	for (const json::value& data : components)
	{
		const std::string& type = data.safeAt("component_type").as_string("");
		Component* const component = TypeFactory::instantiate<Component>(type);
		if (component != nullptr)
		{
			addComponent(component)->deserialize(data);
		}
	}
}

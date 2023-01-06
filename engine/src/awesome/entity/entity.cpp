#include "entity.h"

#include <awesome/core/serialization.h>

void Entity::prepareToSpawn()
{
	for (const auto& component : m_components)
	{
		component->attach(this);
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
		Deserializer::deserialize(prefab->data.value(), *entity);
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
		const auto& component = *it;
		component->uninit();
		component->detach();
		m_components.erase(it);
	}
}

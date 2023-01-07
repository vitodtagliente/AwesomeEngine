#include "entity.h"

#include <awesome/core/serialization.h>

void Entity::prepareToSpawn()
{
	for (const auto& component : m_components)
	{
		component->attach(this);
		component->init();
	}

	for (const auto& child : m_children)
	{
		child->prepareToSpawn();
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
}

void Entity::update(const double deltaTime)
{
	if (m_state == State::PendingSpawn)
	{
		prepareToSpawn();
	}
	if (m_state == State::PendingDestroy) return;

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		const auto& component = *it;
		if (component->enabled)
		{
			component->update(deltaTime);
		}
	}

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		const auto& child = *it;
		if (child->m_state == State::Alive)
		{
			child->update(deltaTime);
		}
		else if (child->m_state == State::PendingDestroy)
		{
			child->prepareToDestroy();
			m_children.erase(it);
			break;
		}
	}

	transform.update();
}

void Entity::queue_destroy()
{
	m_state = State::PendingDestroy;
}

Entity* const Entity::load(const PrefabAssetPtr& prefab)
{
	Entity* const entity = new Entity();
	if (prefab != nullptr && prefab->state == Asset::State::Ready)
	{
		Deserializer::deserialize(prefab->data.value(), *entity);
		entity->m_prefab = prefab;
		entity->m_id = uuid();
	}
	return entity;
}

std::vector<Entity*> Entity::findChildrenByTag(const std::string& childTag) const
{
	std::vector<Entity*> children;
	for (const auto& child : m_children)
	{
		if (child->tag == childTag)
		{
			children.push_back(child.get());
		}

		const auto& childChildren = child->findChildrenByTag(childTag);
		children.insert(children.end(), childChildren.begin(), childChildren.end());
	}
	return children;
}

Entity* const Entity::findChildById(const uuid& childId) const
{
	for (const auto& child : m_children)
	{
		if (child->getId() == childId)
		{
			return child.get();
		}

		Entity* const entity = child->findChildById(childId);
		if (entity != nullptr) return entity;
	}
	return nullptr;
}

Entity* const Entity::findChildByName(const std::string& childName) const
{
	for (const auto& child : m_children)
	{
		if (child->name == childName)
		{
			return child.get();
		}

		Entity* const entity = child->findChildByName(childName);
		if (entity != nullptr) return entity;
	}
	return nullptr;
}

Entity* const Entity::findChildByTag(const std::string& childTag) const
{
	for (const auto& child : m_children)
	{
		if (child->tag == childTag)
		{
			return child.get();
		}

		Entity* const entity = child->findChildByTag(childTag);
		if (entity != nullptr) return entity;
	}
	return nullptr;
}

Entity* const Entity::addChild()
{
	return addChild(math::vec3::zero, math::quaternion::identity);
}

Entity* const Entity::addChild(const math::vec3& position)
{
	return addChild(position, math::quaternion::identity);
}

Entity* const Entity::addChild(const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = new Entity();
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	return addChild(entity);
}

Entity* const Entity::addChild(Entity* const entity)
{
	if (entity != nullptr)
	{
		entity->m_parent = this;
		entity->prepareToSpawn();
		m_children.push_back(std::unique_ptr<Entity>(entity));
	}
	return entity;
}

Entity* const Entity::addChild(const PrefabAssetPtr& prefab)
{
	return addChild(prefab, math::vec3::zero, math::quaternion::identity);
}

Entity* const Entity::addChild(const PrefabAssetPtr& prefab, const math::vec3& position)
{
	return addChild(prefab, position, math::quaternion::identity);
}

Entity* const Entity::addChild(const PrefabAssetPtr& prefab, const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = load(prefab);
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z;
	return addChild(entity);
}

bool Entity::removeChild(Entity* const entity)
{
	return removeChild(entity->getId());
}

bool Entity::removeChild(const uuid& id)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		const auto& child = *it;
		if (child->getId() == id)
		{
			return child->m_state = State::PendingDestroy, true;
		}

		if (child->removeChild(id))
		{
			return true;
		}
	}
	return false;
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

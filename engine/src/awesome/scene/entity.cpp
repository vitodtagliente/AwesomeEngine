#include "entity.h"

Entity::Entity(const uuid& id)
	: m_id(id)
{
}

Entity::Entity(const Entity& other)
	: name(other.name)
	, persistent(other.persistent)
	, replicate(other.replicate)
	, tag(other.tag)
	, transform(other.transform)
	, transient(other.transient)
{
	for (const auto& other_component : other.m_components)
	{
		addComponent(std::make_unique<Component>(*other_component));
	}

	for (const auto& other_child : other.m_children)
	{
		addChild(std::make_unique<Entity>(*other_child));
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

void Entity::update(const double deltaTime)
{
	if (m_state == State::PendingSpawn)
	{
		prepareToSpawn();
	}
	if (m_state == State::PendingDestroy) return;

	m_children.erase(std::remove_if(
		m_children.begin(),
		m_children.end(),
		[](const std::unique_ptr<Entity>& child) -> bool
		{
			return child->m_state == State::PendingDestroy;
		}
		), m_children.end()
	);

	for (auto& entityToSpawn : m_pendingSpawnEntities)
	{
		m_children.push_back(std::move(entityToSpawn));
	}
	m_pendingSpawnEntities.clear();

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		const auto& component = *it;
		if (component->enabled)
		{
			component->update(deltaTime);
		}
	}

	transform.update();

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->update(deltaTime);
	}
}

void Entity::queue_destroy()
{
	m_state = State::PendingDestroy;
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
		if (child->m_id == childId)
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
	std::unique_ptr<Entity> child = std::make_unique<Entity>();
	child->m_parent = this;
	child->prepareToSpawn();
	m_pendingSpawnEntities.push_back(std::move(child));
	return m_pendingSpawnEntities.back().get();
}

Entity* const Entity::addChild(std::unique_ptr<Entity> entity)
{
	if (entity == nullptr) return nullptr;

	entity->m_parent = this;
	entity->prepareToSpawn();
	m_pendingSpawnEntities.push_back(std::move(entity));
	return m_pendingSpawnEntities.back().get();
}

bool Entity::removeChild(Entity* const entity)
{
	return removeChild(entity->m_id);
}

bool Entity::removeChild(const uuid& id)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		const auto& child = *it;
		if (child->m_id == id)
		{
			if (child->persistent) return false;
			return child->m_state = State::PendingDestroy, true;
		}

		if (child->removeChild(id))
		{
			return true;
		}
	}
	return false;
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
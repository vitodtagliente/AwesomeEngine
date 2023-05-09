#include "entity.h"

#include <awesome/graphics/renderer.h>

Entity::Entity(const uuid& id)
	: m_id(id)
{
}

Entity::Entity(const Entity& other)
{
	from_string(other.to_string());
}

Entity& Entity::operator=(const Entity& other)
{
	from_string(other.to_string());
	return *this;
}

bool Entity::operator==(const Entity& other) const
{
	return m_id == other.m_id;
}

bool Entity::operator!=(const Entity& other) const
{
	return m_id != other.m_id;
}

std::size_t Entity::countChildren() const
{
	std::size_t size{ m_children.size() };
	for (const auto& child : m_children)
	{
		size += child->countChildren();
	}
	return size;
}

void Entity::moveChild(Entity* const parent, const uuid& childId)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		const auto& child = *it;
		if (child->m_id == childId)
		{
			parent->addChild(std::move(*it));
			m_children.erase(it);
			return;
		}
	}
}

void Entity::queue_destroy()
{
	m_state = State::PendingDestroy;
	prepareToDestroy();
}

void Entity::render(class graphics::Renderer& renderer)
{
	if (m_state != State::Alive) return;

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		const auto& component = *it;
		if (component->enabled)
		{
			component->render(renderer);
		}
	}

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->render(renderer);
	}
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
		),
		m_children.end()
	);

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

Entity* const Entity::findChildById(const uuid& childId, const bool recursive) const
{
	for (const auto& child : m_children)
	{
		if (child->m_id == childId)
		{
			return child.get();
		}

		if (recursive)
		{
			Entity* const entity = child->findChildById(childId, recursive);
			if (entity != nullptr) return entity;
		}
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
	m_children.push_back(std::move(child));
	return m_children.back().get();
}

Entity* const Entity::addChild(std::unique_ptr<Entity> entity)
{
	if (entity == nullptr) return nullptr;

	entity->m_parent = this;
	entity->prepareToSpawn();
	m_children.push_back(std::move(entity));
	return m_children.back().get();
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
			return child->queue_destroy(), true;
		}

		if (child->removeChild(id))
		{
			return true;
		}
	}
	return false;
}

void Entity::removeChildren()
{
	for (const auto& child : m_children)
	{
		child->queue_destroy();
	}
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
	for (const auto& child : m_children)
	{
		child->prepareToDestroy();
	}

	for (const auto& component : m_components)
	{
		component->uninit();
	}	
}
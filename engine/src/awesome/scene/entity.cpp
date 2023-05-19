#include "entity.h"

#include <awesome/ecs/entities_coordinator.h>
#include <awesome/graphics/renderer.h>

Entity::Entity()
	: storage_id(EntitiesCoordinator::instance().CreateEntity())
{
}

Entity::Entity(const uuid& id)
	: m_id(id)
	, storage_id(EntitiesCoordinator::instance().CreateEntity())
{
}

Entity::Entity(const Entity& other)
	: storage_id(EntitiesCoordinator::instance().CreateEntity())
{
	from_string(other.to_string());
	for (const auto component : other.m_components_runtime)
	{
		m_components.push_back(component->clone());
	}
}

Entity::~Entity()
{
	EntitiesCoordinator::instance().DestroyEntity(storage_id);
}

Entity& Entity::operator=(const Entity& other)
{
	from_string(other.to_string());
	storage_id = EntitiesCoordinator::instance().CreateEntity();
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

void Entity::flush()
{
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

	m_children.insert(
		m_children.end(), 
		std::make_move_iterator(m_pendingSpawnChildren.begin()),
		std::make_move_iterator(m_pendingSpawnChildren.end())
	);
	m_pendingSpawnChildren.clear();
}

void Entity::queue_destroy()
{
	m_state = State::PendingDestroy;
	prepareToDestroy();
}

void Entity::render(class graphics::Renderer& renderer)
{
	if (m_state != State::Alive) return;

	for (auto it = m_components_runtime.begin(); it != m_components_runtime.end(); ++it)
	{
		const auto& component = *it;
		if (component->enabled)
		{
			component->render(renderer);
		}
	}

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

	for (auto it = m_components_runtime.begin(); it != m_components_runtime.end(); ++it)
	{
		const auto& component = *it;
		if (component->enabled)
		{
			component->update(deltaTime);
		}
	}

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
	m_pendingSpawnChildren.push_back(std::move(child));
	return m_pendingSpawnChildren.back().get();
}

Entity* const Entity::addChild(std::unique_ptr<Entity> entity)
{
	if (entity == nullptr) return nullptr;

	entity->m_parent = this;
	entity->prepareToSpawn();
	m_pendingSpawnChildren.push_back(std::move(entity));
	return m_pendingSpawnChildren.back().get();
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

	m_pendingSpawnChildren.clear();
}

void Entity::removeComponent(Component* const component)
{
	removeComponent(component->getId());
}

void Entity::removeComponent(const uuid& id)
{
	const auto& it2 = std::find_if(m_components_runtime.begin(), m_components_runtime.end(), [&id](const Component* component) -> bool
	{
		return component->getId() == id;
	}
	);

	if (it2 != m_components_runtime.end())
	{
		const auto& component = *it2;
		component->uninit();
		component->detach();
		m_components_runtime.erase(it2);
	}

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
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		auto& component = *it;
		if (component->isStorageEnabled())
		{
			auto ptr = component.release();
			m_components_runtime.push_back(ptr->attach(this));
			m_components_runtime.back()->init();
			it = m_components.erase(it);
		}
		else
		{
			component->attach(this);
			component->init();
			++it;
		}
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

	auto it = m_components_runtime.begin();
	while (it != m_components_runtime.end())
	{
		const auto& component = *it;
		component->detach();
		it = m_components_runtime.erase(it);
	}

	for (const auto& component : m_components)
	{
		component->uninit();
	}
}
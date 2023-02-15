/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

#include "component.h"

#include "entity_generated.h"

CLASS(Type = Entity)
class Entity : public Type
{
public:
	enum class State
	{
		PendingSpawn,
		Alive,
		PendingDestroy
	};

	Entity() = default;
	Entity(const uuid& id);
	Entity(const Entity& other) = delete;
	virtual ~Entity() = default;

	Entity& operator= (const Entity& other) = delete;
	bool operator== (const Entity& other) const;
	bool operator!= (const Entity& other) const;

	inline const std::vector<std::unique_ptr<Entity>>& getChildren() const { return m_children; }
	inline const std::vector<std::unique_ptr<Component>>& getComponents() const { return m_components; }
	inline const uuid& getId() const { return m_id; }
	inline Entity* const getParent() const { return m_parent; }
	inline State getState() const { return m_state; }
	inline bool hasChildren() const { return m_children.empty(); }
	inline bool hasParent() const { return m_parent != nullptr; }

	void queue_destroy();
	void update(double deltaTime);

	std::vector<Entity*> findChildrenByTag(const std::string& tag) const;
	Entity* const findChildById(const uuid& id) const;
	Entity* const findChildByName(const std::string& name) const;
	Entity* const findChildByTag(const std::string& tag) const;

	Entity* const addChild();
	bool removeChild(Entity* const entity);
	bool removeChild(const uuid& id);

	template <typename T = Component>
	std::vector<T*> findComponents() const
	{
		std::vector<T*> found_components;
		for (const auto& component : m_components)
		{
			if (T* const found_component = dynamic_cast<T*>(component.get()))
			{
				found_components.push_back(found_component);
			}
		}
		return found_components;
	}

	template <typename T = Component>
	T* const findComponent() const
	{
		for (const auto& component : m_components)
		{
			if (T* const found_component = dynamic_cast<T*>(component.get()))
			{
				return found_component;
			}
		}
		return nullptr;
	}

	template <typename T = Component>
	T* const findComponentInChildren() const
	{
		for (const auto& component : m_components)
		{
			if (T* const found_component = dynamic_cast<T*>(component.get()))
			{
				return found_component;
			}
		}

		for (const auto& child : m_children)
		{
			if (T* const found_component = child->findComponentInChildren<T>())
			{
				return found_component;
			}
		}
		return nullptr;
	}

	template <typename T = Component>
	T* const addComponent()
	{
		T* const component = new T();
		m_components.push_back(std::unique_ptr<Component>(component));
		if (m_state == State::Alive)
		{
			component->attach(this);
			component->init();
		}
		return component;
	}

	Component* const addComponent(Component* const component)
	{
		m_components.push_back(std::unique_ptr<Component>(component));
		if (m_state == State::Alive)
		{
			component->attach(this);
			component->init();
		}
		return component;
	}

	void removeComponent(Component* const component);
	void removeComponent(const uuid& id);

	PROPERTY() std::string name;
	PROPERTY() bool persistent{ false };
	PROPERTY() bool replicate{ false };
	PROPERTY() std::string tag;
	PROPERTY() bool transient{ false };

	GENERATED_BODY()

private:
	void prepareToDestroy();
	void prepareToSpawn();

	PROPERTY() std::vector<std::unique_ptr<Entity>> m_children;
	PROPERTY() std::vector<std::unique_ptr<Component>> m_components;
	PROPERTY() uuid m_id;
	Entity* m_parent{ nullptr };
	std::vector<std::unique_ptr<Entity>> m_pendingSpawnEntities;
	State m_state{ State::PendingSpawn };
};
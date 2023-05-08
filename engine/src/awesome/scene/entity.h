/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/math/transform.h>

#include "component.h"

#include "entity_generated.h"
#include "quad_tree.h"

namespace graphics
{
	class Renderer;
}

CLASS()
class Entity : public IType
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
	Entity(const Entity& other);
	virtual ~Entity() = default;

	Entity& operator= (const Entity& other);
	bool operator== (const Entity& other) const;
	bool operator!= (const Entity& other) const;

	inline const std::vector<std::unique_ptr<Entity>>& children() const { return m_children; }
	inline const std::vector<std::unique_ptr<Component>>& components() const { return m_components; }
	inline const uuid& id() const { return m_id; }
	inline Entity* const parent() const { return m_parent; }
	inline State state() const { return m_state; }
	inline bool hasChildren() const { return !m_children.empty(); }
	inline bool hasParent() const { return m_parent != nullptr; }

	std::size_t countChildren() const;
	void moveChild(Entity* const parent, const uuid& childId);

	void queue_destroy();
	void render(graphics::Renderer& renderer);
	void update(QuadTree& quadtree, double deltaTime);

	std::vector<Entity*> findChildrenByTag(const std::string& tag) const;
	Entity* const findChildById(const uuid& id, bool recursive = true) const;
	Entity* const findChildByName(const std::string& name) const;
	Entity* const findChildByTag(const std::string& tag) const;

	Entity* const addChild();
	Entity* const addChild(std::unique_ptr<Entity> child);
	bool removeChild(Entity* const entity);
	bool removeChild(const uuid& id);
	void removeChildren();

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

	Component* const addComponent(std::unique_ptr<Component> component)
	{
		if (component == nullptr) return nullptr;

		if (m_state == State::Alive)
		{
			component->attach(this);
			component->init();
		}
		m_components.push_back(std::move(component));
		return m_components.back().get();
	}

	void removeComponent(Component* const component);
	void removeComponent(const uuid& id);

	PROPERTY() std::string name;
	PROPERTY() bool persistent{ false };
	PROPERTY() bool replicate{ false };
	PROPERTY() std::string tag;
	PROPERTY() math::transform transform;
	PROPERTY() bool transient{ false };

	GENERATED_BODY()

private:
	void prepareToDestroy();
	void prepareToSpawn();

	PROPERTY() std::vector<std::unique_ptr<Entity>> m_children;
	PROPERTY() std::vector<std::unique_ptr<Component>> m_components;
	uuid m_id;
	Entity* m_parent{ nullptr };
	State m_state{ State::PendingSpawn };
};
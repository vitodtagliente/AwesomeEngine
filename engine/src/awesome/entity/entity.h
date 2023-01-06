/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/asset/prefab_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/math/quaternion.h>
#include <awesome/math/transform.h>

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
	Entity(const Entity& other) = delete;
	virtual ~Entity() = default;

	Entity& operator= (const Entity& other) = delete;
	bool operator== (const Entity& other) const;
	bool operator!= (const Entity& other) const;

	static Entity* const load(const PrefabAssetPtr& prefab);

	inline const std::vector<std::unique_ptr<Entity>>& getChildren() const { return m_children; }
	inline const std::vector<std::unique_ptr<Component>>& getComponents() const { return m_components; }
	inline const uuid& getId() const { return m_id; }
	inline Entity* const getParent() const { return m_parent; }
	inline const PrefabAssetPtr& getPrefab() const { return m_prefab; }
	inline State getState() const { return m_state; }
	inline bool hasParent() const { return m_parent != nullptr; }

	virtual void update(double deltaTime);

	std::vector<Entity*> findChildrenByTag(const std::string& tag) const;
	Entity* const findChildById(const uuid& id) const;
	Entity* const findChildByName(const std::string& name) const;
	Entity* const findChildByTag(const std::string& tag) const;

	Entity* const addChild();
	Entity* const addChild(const math::vec3& position);
	Entity* const addChild(const math::vec3& position, const math::quaternion& quaternion);
	Entity* const addChild(Entity* const entity);
	template <typename T = Entity>
	T* const addChild()
	{
		return addChild(new T());
	}
	Entity* const addChild(const PrefabAssetPtr& prefab);
	Entity* const addChild(const PrefabAssetPtr& prefab, const math::vec3& position);
	Entity* const addChild(const PrefabAssetPtr& prefab, const math::vec3& position, const math::quaternion& quaternion);
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

	void clearChildren();
	void clearComponents();
	void clear();

	PROPERTY() std::string name;
	PROPERTY() bool persistent{ false };
	PROPERTY() bool replicate{ false };
	PROPERTY() std::string tag;
	PROPERTY() math::transform transform;
	PROPERTY() bool transient{ false };

	GENERATED_BODY()

protected:
	virtual void prepareToDestroy();
	virtual void prepareToSpawn();

private:
	PROPERTY() std::vector<std::unique_ptr<Entity>> m_children;
	PROPERTY() std::vector<std::unique_ptr<Component>> m_components;
	PROPERTY() uuid m_id;
	Entity* m_parent{ nullptr };
	PrefabAssetPtr m_prefab;
	State m_state{ State::PendingSpawn };
};
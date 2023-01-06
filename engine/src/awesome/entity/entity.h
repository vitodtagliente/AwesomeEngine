/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/asset/prefab_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/serializable.h>
#include <awesome/core/uuid.h>
#include <awesome/math/transform.h>

#include "component.h"

#include "entity_generated.h"

CLASS(Type = Entity)
class Entity : public Type, public ISerializable
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

	inline const std::vector<std::unique_ptr<Entity>>& getChildren() const { return m_children; }
	inline const std::vector<std::unique_ptr<Component>>& getComponents() const { return m_components; }
	inline const uuid& getId() const { return m_id; }
	inline Entity* const getParent() const { return m_parent; }
	inline const uuid& getPrefab() const { return m_prefab; }
	inline State getState() const { return m_state; }
	inline bool isSpawned() const { return m_state == State::Alive; }

	virtual void prepareToDestroy();
	virtual void prepareToSpawn();
	void setParent(Entity* const entity);
	void update(double deltaTime);

	static Entity* const instantiate(const PrefabAssetPtr& prefab);

	Entity& operator= (const Entity& other) = delete;
	bool operator== (const Entity& other) const;
	bool operator!= (const Entity& other) const;

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
		component->attach(this);
		if (isSpawned())
		{
			component->init();
		}
		return component;
	}

	Component* const addComponent(Component* const component)
	{
		m_components.push_back(std::unique_ptr<Component>(component));
		component->attach(this);
		if (isSpawned())
		{
			component->init();
		}
		return component;
	}

	void removeComponent(Component* const component);
	void removeComponent(const uuid& id);

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	PROPERTY() std::string name;
	PROPERTY() bool persistent{ false };
	PROPERTY() bool replicate{ false };
	PROPERTY() std::string tag;
	PROPERTY() math::transform transform;
	PROPERTY() bool transient{ false };

	GENERATED_BODY()

private:
	std::vector<std::unique_ptr<Entity>> m_children;
	std::vector<std::unique_ptr<Component>> m_components;
	PROPERTY() uuid m_id;
	Entity* m_parent{ nullptr };
	uuid m_prefab{ uuid::Invalid };
	State m_state{ State::PendingSpawn };
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>
#include <awesome/asset/prefab_asset.h>
#include <awesome/encoding/json.h>
#include <awesome/math/transform.h>

#include "component.h"

class World;

namespace graphics
{
	class Renderer;
}

class Entity : public ISerializable
{
public:
	Entity() = default;
	Entity(const Entity& other) = delete;
	~Entity() = default;

	inline const std::vector<std::unique_ptr<Entity>>& getChildren() const { return m_children; }
	inline const std::vector<std::unique_ptr<Component>>& getComponents() const { return m_components; }
	inline const uuid& getId() const { return m_id; }
	inline Entity* const getParent() const { return m_parent; }
	inline const uuid& getPrefab() const { return m_prefab; }
	inline World* const getWorld() const { return m_world; }

	void prepareToDestroy();
	void prepareToSpawn(World* const world);
	void setParent(Entity* const entity);
	void render(graphics::Renderer* const renderer);
	void update(double deltaTime);

	static void duplicate(const Entity& from, Entity& duplicate);
	static void duplicate(const PrefabAssetPtr& prefab, Entity& duplicate);

	Entity& operator= (const Entity& other) = delete;
	bool operator== (const Entity& other) const;
	bool operator!= (const Entity& other) const;

	template <typename T = Component>
	std::vector<T*> getComponents() const
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
		return component;
	}

	Component* const addComponent(Component* const component)
	{
		m_components.push_back(std::unique_ptr<Component>(component));
		component->attach(this);
		return component;
	}

	void removeComponent(Component* const component);
	void removeComponent(const uuid& id);

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	std::string name;
	std::string tag;
	math::transform transform;

private:

	std::vector<std::unique_ptr<Entity>> m_children;
	std::vector<std::unique_ptr<Component>> m_components;
	uuid m_id;
	Entity* m_parent{ nullptr };
	uuid m_prefab{ uuid::Invalid };
	World* m_world{ nullptr };
};
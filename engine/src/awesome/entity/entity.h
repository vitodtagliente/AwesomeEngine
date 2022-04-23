/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>
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
	Entity(const Entity& other);
	Entity(const Entity& other, const uuid& id);
	~Entity() = default;

	inline const uuid& getId() const { return m_id; }
	inline World* const getWorld() const { return m_world; }
	inline Entity* const getParent() const { return m_parent; }
	inline const std::vector<std::unique_ptr<Entity>>& getChildren() const { return m_children; }
	inline const std::vector<std::unique_ptr<Component>>& getComponents() const { return m_components; }

	void prepareToSpawn(World* const world);
	void prepareToDestroy();
	void setParent(Entity* const entity);
	void update(double deltaTime);
	void render(graphics::Renderer* const renderer);

	Entity& operator= (const Entity& other);
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

	uuid m_id;
	World* m_world;
	Entity* m_parent;
	std::vector<std::unique_ptr<Entity>> m_children;
	std::vector<std::unique_ptr<Component>> m_components;
};
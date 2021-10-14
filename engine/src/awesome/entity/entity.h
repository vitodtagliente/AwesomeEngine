/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/string_id.h>
#include <awesome/math/transform.h>

#include "component.h"

class World;

namespace graphics
{
	class Renderer;
}

class Entity
{
public:
	Entity(World* const world);
	~Entity();

	inline const string_id& getId() const { return m_id; }
	inline World* const getWorld() const { return m_world; }
	inline Entity* const getParent() const { return m_parent; }
	inline const std::vector<Entity*>& getChildren() const { return m_children; }
	inline const std::vector<Component*>& getComponents() const { return m_components; }
	inline std::vector<Component*>& getComponents() { return m_components; }

	void prepareToSpawn();
	void prepareToDestroy();
	void setParent(Entity* const entity);
	void update(double deltaTime);
	void render(graphics::Renderer* const renderer);

	template <typename T = Component>
	std::vector<T*> getComponents() const
	{
		std::vector<T*> found_components;
		for (Component* const component : m_components)
		{
			if (T* const found_component = dynamic_cast<T*>(component))
			{
				found_components.push_back(found_component);
			}
		}
		return found_components;
	}

	template <typename T = Component>
	T* const findComponent() const
	{
		for (Component* const component : m_components)
		{
			if (T* const found_component = dynamic_cast<T*>(component))
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
		m_components.push_back(component);
		component->attach(this);
		return component;
	}

	void removeComponent(Component* const component);

	std::string name;
	std::string tag;
	math::transform transform;

private:

	string_id m_id;
	World* const m_world;
	Entity* m_parent;
	std::vector<Entity*> m_children;
	std::vector<Component*> m_components;
};
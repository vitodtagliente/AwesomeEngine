/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>
#include <awesome/core/string_id.h>
#include <vdtmath/transform.h>

#include "component.h"

class World;

namespace graphics
{
	class Renderer;
}

class Entity
{
public:

	std::string name;
	std::string tag;
	math::transform transform;

	inline Entity* const getParent()const { return m_parent; }
	inline const std::vector<Entity*>& getChildren() const { return m_children; }

	void prepareToSpawn(World& world);
	void prepareToDestroy();
	void setParent(Entity* const entity);
	void update(World& world, double deltaTime);
	void render(graphics::Renderer& renderer);

	template <typename T = Component>
	std::vector<T*> getComponents() const
	{
		std::vector<T*> found_components;
		for (Component* const component : m_components)
		{
			if (T* const found_component = dynamic_cast<T*>(component))
				found_components.push_back(found_component);
		}
		return std::move(found_components);
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

private:

	string_id m_id;
	Entity* m_parent;
	std::vector<Entity*> m_children;
	std::vector<Component*> m_components;
};
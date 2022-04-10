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
	~Entity() = default;

	inline const uuid& getId() const { return m_id; }
	inline World* const getWorld() const { return m_world; }
	inline const std::shared_ptr<Entity>& getParent() const { return m_parent; }
	inline const std::vector<std::shared_ptr<Entity>>& getChildren() const { return m_children; }
	inline const std::vector<Component*>& getComponents() const { return m_components; }
	inline std::vector<Component*>& getComponents() { return m_components; }

	void prepareToSpawn(World* const world);
	void prepareToDestroy();
	void setParent(const std::shared_ptr<Entity>& entity);
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

	Component* const addComponent(Component* const component)
	{
		m_components.push_back(component);
		component->attach(this);
		return component;
	}

	void removeComponent(Component* const component);

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	std::string name;
	std::string tag;
	math::transform transform;

private:

	uuid m_id;
	World* m_world;
	std::shared_ptr<Entity> m_parent;
	std::vector<std::shared_ptr<Entity>> m_children;
	std::vector<Component*> m_components;
};

typedef std::shared_ptr<Entity> EntityPtr;
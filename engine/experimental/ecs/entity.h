/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "core/plf_hive.h"
#include "core/uuid.h"
#include "math/transform2.h"

#include "component.h"
#include "component_array.h"

class EntityManager;
class EntityPtr;

class Entity
{
public:
	inline bool operator== (const Entity& other) const { return m_id == other.m_id; }
	inline bool operator!= (const Entity& other) const { return m_id != other.m_id; }

	inline const uuid& id() const { return m_id; }

	void queue_free();

	template <typename T = Component>
	T& addComponent()
	{
		const std::size_t component_id = ComponentArray<T>::instance().id();

		const auto& it = EntityManager::s_components.find(m_id);
		if (it != EntityManager::s_components.end())
		{
			it->second |= component_id;
		}
		else
		{
			EntityManager::s_components.insert(std::make_pair(m_id, component_id));
		}

		return ComponentArray<T>::instance().push_back(m_id, T{});
	}

	template <typename T = Component>
	T* const findComponent()
	{
		return dynamic_cast<T*>(ComponentArray<T>::instance().find(m_id));
	}

	template <typename T = Component>
	void removeComponent()
	{
		const std::size_t component_id = ComponentArray<T>::instance().id();

		const auto& it = EntityManager::s_components.find(m_id);
		if (it != EntityManager::s_components.end())
		{
			if ((it->second & component_id) != 0)
			{
				it->second &= ~component_id;
				ComponentArray<T>::instance().queue_free(m_id);
			}
		}
	}

	std::string name;
	bool persistent{ false };
	bool replicate{ false };
	std::string tag;
	math::transform2 transform;
	bool transient{ false };

private:
	uuid m_id;
};

class EntityManager
{
public:
	friend class Entity;
	friend class EntityPtr;

	inline static std::size_t& components(const uuid& entity)
	{
		return s_components[entity];
	}

	static Entity* const find(const uuid& id);
	static Entity& get(const uuid& id);

	inline static plf::hive<Entity>& entities()
	{
		return s_entities;
	}

	static void clear();
	static void flush();

	static Entity& spawn();

	static void queue_free(const uuid& entity);

private:
	static inline plf::hive<Entity> s_entities;
	static inline std::map<uuid, std::size_t> s_components;
	static inline std::map<uuid, Entity*> s_lookup;

	static inline std::queue<uuid> s_pendingDeleteEntities;
};
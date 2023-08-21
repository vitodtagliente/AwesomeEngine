/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cmath>
#include <map>
#include <queue>
#include <vector>

#include "core/plf_hive.h"
#include "core/uuid.h"

#include "component.h"

class IComponentArray
{
public:
	friend class ComponentRegistry;

	inline std::size_t id() const { return m_id; }

	virtual void clear() = 0;
	virtual void flush() = 0;
	virtual void erase(const uuid& entity) = 0;
	virtual void queue_free(const uuid& entity) = 0;

	virtual Component* const find(const uuid& entity) = 0;

private:
	std::size_t m_id{ 0 };
};

class ComponentRegistry
{
public:
	template <typename T>
	friend class ComponentArray;

	static IComponentArray* const find(const std::size_t id);
	static IComponentArray& get(const std::size_t id);

	inline static std::vector<IComponentArray*>& components()
	{
		return s_components;
	}

	static void clear();
	static void flush();

	static void erase(const uuid& entity);
	static void queue_free(const uuid& entity);

private:
	static void register_component(IComponentArray* const instance);

	static inline std::vector<IComponentArray*> s_components;
	static inline std::map<std::size_t, IComponentArray*> s_lookup;
};

template <typename T = Component>
class ComponentArray final : public IComponentArray
{
public:
	template <typename C>
	friend class ComponentPtr;

	typedef T data_t;

	plf::hive<data_t>& data() { return m_data; }
	std::vector<uuid>& entities() { return m_entities; }

	virtual void clear() override;
	virtual void flush() override;
	virtual void erase(const uuid& entity) override;
	virtual void queue_free(const uuid& entity) override;

	virtual Component* const find(const uuid& entity_id) override;
	T& get(const uuid& entity_id);

	T& push_back(const uuid& entity_id, const T& data);
	template <typename ...P>
	T& push_back(const uuid& entity_id, P... args);

	static ComponentArray<T>& instance()
	{
		static ComponentArray<T> s_instance;
		return s_instance;
	}

private:
	ComponentArray()
	{
		ComponentRegistry::register_component(this);
	}

	plf::hive<data_t> m_data;
	std::vector<uuid> m_entities;
	std::map<uuid, data_t*> m_lookup;

	std::vector<std::pair<uuid, data_t>> m_pendingSpawnData;

	std::queue<uuid> m_pendingDeleteEntities;
};

template<typename T>
void ComponentArray<T>::clear()
{
	m_data.clear();
	m_entities.clear();
	m_lookup.clear();

	m_pendingSpawnData.clear();

	while (m_pendingDeleteEntities.empty() == false)
	{
		m_pendingDeleteEntities.pop();
	}
}

template <typename T>
void ComponentArray<T>::flush()
{
	for (int i = 0; i < m_pendingSpawnData.size(); ++i)
	{
		std::pair<uuid, data_t>& data = m_pendingSpawnData[i];
		T* const component = &*m_data.insert(std::move(data.second));
		m_lookup.insert(std::make_pair(data.first, component));
		m_entities.push_back(data.first);

		component->m_entity = data.first;
		component->init();
	}

	m_pendingSpawnData.clear();

	while (m_pendingDeleteEntities.empty() == false)
	{
		const uuid& id = m_pendingDeleteEntities.front();

		erase(id);

		m_pendingDeleteEntities.pop();
	}
}

template <typename T>
void ComponentArray<T>::erase(const uuid& entity_id)
{
	const auto& it = m_lookup.find(entity_id);
	if (it != m_lookup.end())
	{
		it->second->uninit();
		
		m_lookup.erase(it);
	}
}

template <typename T>
void ComponentArray<T>::queue_free(const uuid& entity_id)
{
	m_pendingDeleteEntities.push(entity_id);
}

template <typename T>
Component* const ComponentArray<T>::find(const uuid& entity_id)
{
	const auto& it = m_lookup.find(entity_id);
	if (it != m_lookup.end())
	{
		return it->second;
	}
	return nullptr;
}

template <typename T>
T& ComponentArray<T>::get(const uuid& entity_id)
{
	return *m_lookup[entity_id];
}

template <typename T>
T& ComponentArray<T>::push_back(const uuid& entity_id, const T& data)
{
	const auto& it = m_lookup.find(entity_id);
	if (it != m_lookup.end())
	{
		return *it->second;
	}

	m_pendingSpawnData.push_back(std::make_pair(entity_id, std::move(data)));
	return m_pendingSpawnData.back().second;
}

template <typename T>
template <typename ...P>
T& ComponentArray<T>::push_back(const uuid& entity_id, P... args)
{
	const auto& it = m_lookup.find(entity_id);
	if (it != m_lookup.end())
	{
		return *it->second;
	}

	m_pendingSpawnData.push_back(std::make_pair(entity_id, T{ std::forward<P>(args)... }));
	return m_pendingSpawnData.back();
}
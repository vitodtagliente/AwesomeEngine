/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "types.h"

#include <awesome/scene/component.h>

#include <array>
#include <cassert>
#include <unordered_map>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(EntityStorageId entity) = 0;
};

template<typename T>
class ComponentArray final : public IComponentArray
{
public:
	ComponentArray()
	{
		//m_componentArray.reserve(MAX_ENTITIES);
	}

	T& InsertData(EntityStorageId entity, T component)
	{
		assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end
		size_t newIndex = m_size;
		m_entityToIndexMap[entity] = newIndex;
		m_indexToEntityMap[newIndex] = entity;

		m_componentArray[newIndex] = std::move(component);
		++m_size;
		return m_componentArray[newIndex];
	}

	void RemoveData(EntityStorageId entity)
	{
		assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
		size_t indexOfLastElement = m_size - 1;
		m_componentArray[indexOfRemovedEntity] = std::move(m_componentArray[indexOfLastElement]);
		//T* p1 = m_componentArray.data() + indexOfRemovedEntity;
		//T* p2 = m_componentArray.data() + indexOfLastElement;
		//std::swap(p1, p2);
		//std::iter_swap(std::begin(m_componentArray) + indexOfRemovedEntity, std::begin(m_componentArray) + indexOfLastElement);

		// Update map to point to moved spot
		EntityStorageId entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
		m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		m_entityToIndexMap.erase(entity);
		m_indexToEntityMap.erase(indexOfLastElement);

		--m_size;
	}

	T& GetData(EntityStorageId entity)
	{
		assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");

		return m_componentArray[m_entityToIndexMap[entity]];
	}

	void EntityDestroyed(EntityStorageId entity) override
	{
		if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> m_componentArray{};
	std::unordered_map<EntityStorageId, size_t> m_entityToIndexMap{};
	std::unordered_map<size_t, EntityStorageId> m_indexToEntityMap{};
	size_t m_size{ 0 };
};

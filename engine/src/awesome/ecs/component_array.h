/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "types.h"

#include <awesome/scene/component.h>
#include <awesome/scene/entity.h>

#include <awesome/core/logger.h>

#include <array>
#include <cassert>
#include <unordered_map>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(StoragableEntity<Entity>& entity) = 0;
};

template<typename T>
class ComponentArray final : public IComponentArray
{
public:
	ComponentArray()
	{
		//m_componentArray.reserve(MAX_ENTITIES);
	}

	T& InsertData(StoragableEntity<Entity>& entity, T component)
	{
		assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end
		size_t newIndex = m_size;
		m_entityToIndexMap[entity] = newIndex;
		m_indexToEntityMap[newIndex] = entity;

		INFO_LOG("ECS", THIS_FUNC + std::string("inserting component:") + std::string(typeid(T).name()) + std::string("entity:") + std::to_string(entity.getStorageId()) + std::string(", stored owner") + std::to_string(component.getOwner()->storageRef.getStorageId()) + "newIndex:" + std::to_string(newIndex));

		m_componentArray[newIndex] = std::move(component);
		++m_size;
		return m_componentArray[newIndex];
	}

	void RemoveData(StoragableEntity<Entity>& entity)
	{
		assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
		size_t indexOfLastElement = m_size - 1;
		INFO_LOG("ECS", THIS_FUNC + std::string("removing entity:") + std::to_string(entity.getStorageId()) + "indexOfRemovedEntity:" + std::to_string(indexOfRemovedEntity) + ", indexOfLastElement:" + std::to_string(indexOfLastElement));
		if (indexOfLastElement != indexOfRemovedEntity)
		{
			m_componentArray[indexOfRemovedEntity] = std::move(m_componentArray[indexOfLastElement]);
			// Update map to point to moved spot
			StoragableEntity<Entity>& entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
			m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
			entityOfLastElement.onRelocation(&m_componentArray[indexOfRemovedEntity]);
		}
		m_entityToIndexMap.erase(entity);
		m_indexToEntityMap.erase(indexOfLastElement);
		--m_size;
	}

	T& GetData(StoragableEntity<Entity>& entity)
	{
		assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");

		return m_componentArray[m_entityToIndexMap[entity]];
	}

	void EntityDestroyed(StoragableEntity<Entity>& entity) override
	{
		if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> m_componentArray{};
	std::unordered_map<StoragableEntity<Entity>, size_t> m_entityToIndexMap{};
	std::unordered_map<size_t, StoragableEntity<Entity>> m_indexToEntityMap{};
	size_t m_size{ 0 };
};

/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "component_array.h"
#include "types.h"

#include <awesome/scene/entity.h>

#include <any>
#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentContainers.find(typeName) == m_componentContainers.end() && "Registering component type more than once.");

		m_componentContainers.insert({ typeName, m_nextComponentContainerId });
		m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++m_nextComponentContainerId;
	}

	template<typename T>
	ComponentContainerId GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentContainers.find(typeName) != m_componentContainers.end() && "Component not registered before use.");

		return m_componentContainers[typeName];
	}

	template<typename T>
	T& AddComponent(StoragableEntity<Entity>& entity, T component)
	{
		return GetComponentArray<T>()->InsertData(entity, std::move(component));
	}

	template<typename T>
	void RemoveComponent(StoragableEntity<Entity>& entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(StoragableEntity<Entity>& entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(StoragableEntity<Entity>& entity)
	{
		for (auto const& pair : m_componentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentContainerId> m_componentContainers{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};
	ComponentContainerId m_nextComponentContainerId{};


	template<typename T = Component>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentContainers.find(typeName) != m_componentContainers.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
	}
};

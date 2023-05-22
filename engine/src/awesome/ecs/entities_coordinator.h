/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "component_manager.h"
#include "entity_manager.h"
#include "entity_systems_manager.h"
#include "types.h"

#include <awesome/core/singleton.h>
#include <awesome/scene/entity.h>

#include <memory>


class EntitiesCoordinator final : public Singleton<EntitiesCoordinator>
{
public:

	void Init()
	{
		m_componentManager = std::make_unique<ComponentManager>();
		m_entityManager = std::make_unique<EntityManager>();
		m_systemManager = std::make_unique<EntitySystemManager>();
	}

	// EntityStorageId methods
	StoragableEntity<Entity> CreateEntity()
	{
		return StoragableEntity<Entity>(m_entityManager->CreateEntity());
	}

	void DestroyEntity(StoragableEntity<Entity>& entity)
	{
		m_entityManager->DestroyEntity(entity.getStorageId());
		m_componentManager->EntityDestroyed(entity);
		m_systemManager->EntityDestroyed(entity);
	}

	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		m_componentManager->RegisterComponent<T>();
	}

	template<typename T>
	T& AddComponent(StoragableEntity<Entity>& entity, T component)
	{
		auto& tmp = m_componentManager->AddComponent<T>(entity, std::move(component));

		auto signature = m_entityManager->GetSignature(entity.getStorageId());
		signature.set(m_componentManager->GetComponentType<T>(), true);
		m_entityManager->SetSignature(entity.getStorageId(), signature);

		m_systemManager->EntitySignatureChanged(entity, signature);

		return tmp;
	}

	template<typename T>
	void RemoveComponent(StoragableEntity<Entity>& entity)
	{
		m_componentManager->RemoveComponent<T>(entity);

		auto signature = m_entityManager->GetSignature(entity.getStorageId());
		signature.set(m_componentManager->GetComponentType<T>(), false);
		m_entityManager->SetSignature(entity.getStorageId(), signature);

		m_systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(StoragableEntity<Entity>& entity)
	{
		return m_componentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentContainerId GetComponentType()
	{
		return m_componentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return m_systemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		m_systemManager->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> m_componentManager;
	std::unique_ptr<EntityManager> m_entityManager;
	std::unique_ptr<EntitySystemManager> m_systemManager;
};

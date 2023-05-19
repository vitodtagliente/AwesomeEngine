/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "types.h"

#include <awesome/scene/component.h>

#include <array>
#include <cassert>
#include <queue>


class EntityManager
{
public:
	EntityManager()
	{
		for (EntityStorageId entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			m_availableEntities.push(entity);
		}
	}

	EntityStorageId CreateEntity()
	{
		assert(m_livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		EntityStorageId id = m_availableEntities.front();
		m_availableEntities.pop();
		++m_livingEntityCount;

		return id;
	}

	void DestroyEntity(EntityStorageId entity)
	{
		assert(entity < MAX_ENTITIES && "EntityStorageId out of range.");

		m_signatures[entity].reset();
		m_availableEntities.push(entity);
		--m_livingEntityCount;
	}

	void SetSignature(EntityStorageId entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "EntityStorageId out of range.");

		m_signatures[entity] = signature;
	}

	Signature GetSignature(EntityStorageId entity)
	{
		assert(entity < MAX_ENTITIES && "EntityStorageId out of range.");

		return m_signatures[entity];
	}

private:
	std::queue<EntityStorageId> m_availableEntities{};
	std::array<Signature, MAX_ENTITIES> m_signatures{};
	uint32_t m_livingEntityCount{};
};

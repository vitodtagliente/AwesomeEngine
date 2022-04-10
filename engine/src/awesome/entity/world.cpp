#include "world.h"

#include <awesome/graphics/renderer.h>

void World::update(const double deltaTime)
{
	for (const auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void World::render(graphics::Renderer* const renderer)
{
	for (const auto& entity : m_entities)
	{
		entity->render(renderer);
	}
}

void World::flush()
{
	for (const auto& entity : m_pendingSpawnEntities)
	{
		m_entities.push_back(entity);
	}
	m_pendingSpawnEntities.clear();

	for (const auto& entity : m_pendingDestroyEntities)
	{
		auto destroyIt = std::find(m_entities.begin(), m_entities.end(), entity);
		if (destroyIt != m_entities.end())
		{
			(*destroyIt)->prepareToDestroy();
			m_entities.erase(destroyIt);
		}
	}
	m_pendingDestroyEntities.clear();
}

std::vector<EntityPtr> World::findEntitiesByTag(const std::string& tag) const
{
	std::vector<EntityPtr> entities;
	for (const auto& entity : m_entities)
	{
		if (entity->tag == tag)
		{
			entities.push_back(entity);
		}
	}
	return entities;
}

EntityPtr const World::findEntityById(const uuid& id) const
{
	const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [&id](const EntityPtr& entity) -> bool 
		{
			return entity->getId() == id;
		}
	);

	if (it != m_entities.end())
	{
		return *it;
	}
	return nullptr;
}

EntityPtr const World::findEntityByName(const std::string& name) const
{
	const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [&name](const EntityPtr& entity) -> bool
		{
			return entity->name == name;
		}
	);

	if (it != m_entities.end())
	{
		return *it;
	}
	return nullptr;
}

EntityPtr const World::spawn()
{
	return spawn(vec3::zero, quaternion::identity);
}

EntityPtr const World::spawn(const vec3& position)
{
	return spawn(position, quaternion::identity);
}

EntityPtr const World::spawn(const math::vec3& position, const math::quaternion& quaternion)
{
	EntityPtr entity = std::make_shared<Entity>();
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	entity->prepareToSpawn(this);
	m_pendingSpawnEntities.push_back(entity);

	return entity;
}

EntityPtr const World::spawn(const Entity& prefab)
{
	return spawn(prefab, vec3::zero, quaternion::identity);
}

EntityPtr const World::spawn(const Entity& prefab, const vec3& position)
{
	return spawn(prefab, position, quaternion::identity);
}

EntityPtr const World::spawn(const Entity& prefab, const vec3& position, const quaternion& quaternion)
{
	EntityPtr entity = spawn(position, quaternion);
	entity->deserialize(prefab.serialize());
	return entity;
}

void World::destroy(const EntityPtr& entity)
{
	m_pendingDestroyEntities.push_back(entity);
}

void World::clear()
{
	for (const auto& entity : m_entities)
	{
		destroy(entity);
	}
}

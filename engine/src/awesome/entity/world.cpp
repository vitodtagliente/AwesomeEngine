#include "world.h"

#include <awesome/graphics/renderer.h>

World::World()
	: m_entities()
	, m_pendingSpawnEntities()
	, m_pendingDestroyEntities()
{
}

World::~World()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		delete entity;
	}
	m_entities.clear();

	for (auto it = m_pendingSpawnEntities.begin(); it != m_pendingSpawnEntities.end(); ++it)
	{
		Entity* const entity = *it;
		delete entity;
	}
	m_pendingSpawnEntities.clear();

	for (auto it = m_pendingDestroyEntities.begin(); it != m_pendingDestroyEntities.end(); ++it)
	{
		Entity* const entity = *it;
		delete entity;
	}
	m_pendingDestroyEntities.clear();
}

void World::update(const double deltaTime)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		entity->update(deltaTime);
	}
}

void World::render(graphics::Renderer* const renderer)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		entity->render(renderer);
	}
}

void World::flush()
{
	for (auto it = m_pendingSpawnEntities.begin(); it != m_pendingSpawnEntities.end(); ++it)
	{
		m_entities.push_back(*it);
	}
	m_pendingSpawnEntities.clear();

	for (auto it = m_pendingDestroyEntities.begin(); it != m_pendingDestroyEntities.end(); ++it)
	{
		auto destroyIt = std::find(m_entities.begin(), m_entities.end(), *it);
		if (destroyIt != m_entities.end())
		{
			(*destroyIt)->prepareToDestroy();
			delete *destroyIt;
			*destroyIt = nullptr;
			m_entities.erase(destroyIt);
		}
	}
	m_pendingDestroyEntities.clear();
}

std::vector<Entity*> World::findEntitiesByTag(const std::string& tag) const
{
	std::vector<Entity*> entities;
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		if (entity->tag == tag)
		{
			entities.push_back(entity);
		}
	}
	return entities;
}

Entity* const World::findEntityByName(const std::string& name) const
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		if (entity->name == name)
		{
			return entity;
		}
	}
	return nullptr;
}

Entity* const World::spawn()
{
	return spawn(vec3::zero, quaternion::identity);
}

Entity* const World::spawn(const vec3& position)
{
	return spawn(position, quaternion::identity);
}

Entity* const World::spawn(const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = new Entity(this);
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	entity->prepareToSpawn();
	m_pendingSpawnEntities.push_back(entity);

	return entity;
}

void World::destroy(Entity* const entity)
{
	m_pendingDestroyEntities.push_back(entity);
}

void World::clear()
{
	for (Entity* const entity : m_entities)
	{
		destroy(entity);
	}
}

json::value World::toJson() const
{
	return json::value();
}

void World::fromJson(const json::value&)
{
}

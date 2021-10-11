#include "world.h"

#include <awesome/graphics/renderer.h>

#include "entity.h"

World::World()
	: m_entities()
{
}

void World::update(double deltaTime)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		entity->update(*this, deltaTime);
	}
}

void World::render(graphics::Renderer& renderer)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		entity->render(renderer);
	}
}

std::vector<Entity*> World::getEntitiesByTag(const std::string& tag)
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

Entity* const World::spawn(const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = new Entity;
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z;
	entity->prepareToSpawn(*this);
	m_entities.push_back(entity);

	return entity;
}

void World::destroy(Entity* const entity)
{
	// auto it = std::find(m_entities.begin(), m_entities.end(), entity);
	// if (it != m_entities.end())
	// {
	// 	entity->prepareToDestroy();
	// 	m_entities.erase(it);
	// 	delete entity;
	// }
}

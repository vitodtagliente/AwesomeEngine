#include "world.h"

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

void World::render()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* const entity = *it;
		entity->render();
	}
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
	// TODO
}

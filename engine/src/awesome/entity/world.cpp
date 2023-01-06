#include "world.h"

#include <awesome/component/collider2d_component.h>

void World::update(const double deltaTime)
{
	// quadtree update & parenting
	for (const auto& child : m_children)
	{
		Collider2dComponent* const collider = child->findComponent<Collider2dComponent>();
		if (collider != nullptr)
		{
			m_quadspace.insert(child.get(), 12);
		}
	}

	// sort the entities by depth
	std::sort(m_children.begin(), m_children.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) -> bool
		{
			return a->transform.position.z < b->transform.position.z;
		}
	);

	Entity::update(deltaTime);
	
	checkCollisions();
}

void World::flush()
{
	m_quadspace.clear();
}

Entity* const World::findNearestEntity(Entity* const entity) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);
	if (entities.empty()) return nullptr;

	int nearestIndex = 0;
	float minDistance = entity->transform.position.distance(entities[0]->transform.position);
	for (int i = 1; i < entities.size(); ++i)
	{
		const float distance = entity->transform.position.distance(entities[i]->transform.position);
		if (distance < minDistance)
		{
			minDistance = distance;
			nearestIndex = i;
		}
	}
	return entities[nearestIndex];
}

Entity* const World::findNearestEntityByTag(Entity* const entity, const std::string& entityTag) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);
	if (entities.empty()) return nullptr;

	int nearestIndex = -1;
	float minDistance = 0;
	for (int i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->tag != entityTag) continue;

		const float distance = entity->transform.position.distance(entities[i]->transform.position);

		if (nearestIndex == -1)
		{
			nearestIndex = i;
			minDistance = distance;
			continue;
		}

		if (distance < minDistance)
		{
			minDistance = distance;
			nearestIndex = i;
		}
	}

	if (nearestIndex == -1) return nullptr;
	return entities[nearestIndex];
}

std::vector<Entity*> World::findNearestEntities(Entity* const entity) const
{
	return m_quadspace.retrieve(entity);
}

std::vector<Entity*> World::findNearestEntities(Entity* const entity, const float distance) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);

	entities.erase(std::remove_if(entities.begin(), entities.end(), [entity, distance](Entity* const nearEntity) -> bool
			{
				return entity->transform.position.distance(nearEntity->transform.position) > distance;
			}
		), entities.end()
	);

	return entities;
}

std::vector<Entity*> World::findNearestEntitiesByTag(Entity* const entity, const std::string& entityTag) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);

	entities.erase(std::remove_if(entities.begin(), entities.end(), [entityTag](Entity* const nearEntity) -> bool
		{
			return nearEntity->tag != entityTag;
		}
		), entities.end()
	);

	return entities;
}

std::vector<Entity*> World::findNearestEntitiesByTag(Entity* const entity, const float distance, const std::string& entityTag) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);

	entities.erase(std::remove_if(entities.begin(), entities.end(), [entity, distance, entityTag](Entity* const nearEntity) -> bool
		{
			return nearEntity->tag != entityTag || entity->transform.position.distance(nearEntity->transform.position) > distance;
		}
		), entities.end()
	);

	return entities;
}

void World::clear()
{
	m_children.clear();
	m_scene.reset();
}

void World::load(const SceneAssetPtr& scene)
{
	m_scene = scene;

	clear();
}

void World::save(const std::filesystem::path& path)
{
	// JsonFile::save(*this, path);
	// 
	// AssetImporter importer;
	// importer.import(path, );
}

void World::checkCollisions()
{
	for (const auto& child : m_children)
	{
		Collider2dComponent* const collider = child->findComponent<Collider2dComponent>();
		if (collider == nullptr) continue;

		for (Entity* const other : findNearestEntities(child.get()))
		{
			Collider2dComponent* const otherCollider = other->findComponent<Collider2dComponent>();
			if (otherCollider == nullptr) continue;

			collider->collide(*otherCollider);
		}
	}
}

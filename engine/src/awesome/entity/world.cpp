#include "world.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/core/serialization.h>
#include <awesome/component/collider2d_component.h>
#include <awesome/data/json_file.h>

void World::update(const double deltaTime, const int quadspaceBounds)
{
	// quadtree update & parenting
	for (const auto& entity : m_entities)
	{
		Collider2dComponent* const collider = entity->findComponent<Collider2dComponent>();
		if (collider != nullptr)
		{
			m_quadspace.insert(entity.get(), quadspaceBounds);
		}
	}

	// sort the entities by depth
	std::sort(m_entities.begin(), m_entities.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) -> bool
		{
			return a->transform.position.z < b->transform.position.z;
		}
	);

	// entities update
	for (const auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
	
	checkCollisions();
}

void World::flush()
{
	for (const uuid& entityToDestroy : m_pendingDestroyEntities)
	{
		const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [entityToDestroy](const std::unique_ptr<Entity>& entity) -> bool
			{
				return entity->getId() == entityToDestroy;
			}
		);

		if (it != m_entities.end())
		{
			(*it)->prepareToDestroy();
			m_entities.erase(it);
		}
	}
	m_pendingDestroyEntities.clear();

	for (auto& entityToSpawn : m_pendingSpawnEntities)
	{
		m_entities.push_back(std::move(entityToSpawn));
	}
	m_pendingSpawnEntities.clear();
	m_quadspace.clear();
}

std::vector<Entity*> World::findEntitiesByTag(const std::string& tag) const
{
	std::vector<Entity*> entities;
	for (const auto& entity : m_entities)
	{
		if (entity->tag == tag)
		{
			entities.push_back(entity.get());
		}
	}
	return entities;
}

Entity* const World::findEntityById(const uuid& id) const
{
	const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [&id](const std::unique_ptr<Entity>& entity) -> bool
		{
			return entity->getId() == id;
		}
	);

	if (it != m_entities.end())
	{
		return it->get();
	}
	return nullptr;
}

Entity* const World::findEntityByName(const std::string& name) const
{
	const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [&name](const std::unique_ptr<Entity>& entity) -> bool
		{
			return entity->name == name;
		}
	);

	if (it != m_entities.end())
	{
		return it->get();
	}
	return nullptr;
}

Entity* const World::findEntityByTag(const std::string& tag) const
{
	const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [&tag](const std::unique_ptr<Entity>& entity) -> bool
		{
			return entity->tag == tag;
		}
	);

	if (it != m_entities.end())
	{
		return it->get();
	}
	return nullptr;
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

Entity* const World::findNearestEntityByTag(Entity* const entity, const std::string& tag) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);
	if (entities.empty()) return nullptr;

	int nearestIndex = -1;
	float minDistance = 0;
	for (int i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->tag != tag) continue;

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

std::vector<Entity*> World::findNearestEntitiesByTag(Entity* const entity, const std::string& tag) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);

	entities.erase(std::remove_if(entities.begin(), entities.end(), [tag](Entity* const nearEntity) -> bool
		{
			return nearEntity->tag != tag;
		}
		), entities.end()
	);

	return entities;
}

std::vector<Entity*> World::findNearestEntitiesByTag(Entity* const entity, const float distance, const std::string& tag) const
{
	std::vector<Entity*> entities = m_quadspace.retrieve(entity);

	entities.erase(std::remove_if(entities.begin(), entities.end(), [entity, distance, tag](Entity* const nearEntity) -> bool
		{
			return nearEntity->tag != tag || entity->transform.position.distance(nearEntity->transform.position) > distance;
		}
		), entities.end()
	);

	return entities;
}

Entity* const World::spawn()
{
	return spawn(math::vec3::zero, math::quaternion::identity);
}

Entity* const World::spawn(const math::vec3& position)
{
	return spawn(position, math::quaternion::identity);
}

Entity* const World::spawn(const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = new Entity();
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	return spawn(entity);
}

Entity* const World::spawn(Entity* const entity)
{
	if (entity != nullptr)
	{
		entity->prepareToSpawn();
		m_pendingSpawnEntities.push_back(std::unique_ptr<Entity>(entity));
	}
	return entity;
}

Entity* const World::spawn(const PrefabAssetPtr& prefab)
{
	return spawn(prefab, math::vec3::zero, math::quaternion::identity);
}

Entity* const World::spawn(const PrefabAssetPtr& prefab, const math::vec3& position)
{
	return spawn(prefab, position, math::quaternion::identity);
}

Entity* const World::spawn(const PrefabAssetPtr& prefab, const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = Entity::instantiate(prefab);
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z;
	return spawn(entity);
}

void World::destroy(Entity* const entity)
{
	m_pendingDestroyEntities.push_back(entity->getId());
}

void World::destroy(const uuid& id)
{
	m_pendingDestroyEntities.push_back(id);
}

void World::clear()
{
	m_pendingSpawnEntities.clear();
	m_pendingDestroyEntities.clear();
	m_entities.clear();
}

bool World::isLoading(size_t& progress) const
{
	return progress = 0, false;
}

void World::load(const SceneAssetPtr& scene)
{
	m_loadedSceneId = scene->descriptor.id;

	clear();
}

void World::save(const std::filesystem::path& path)
{
	JsonFile::save(*this, path);

	AssetImporter importer;
	importer.import(path, m_loadedSceneId);
}

void World::checkCollisions()
{
	for (const auto& entity : m_entities)
	{
		Collider2dComponent* const collider = entity->findComponent<Collider2dComponent>();
		if (collider == nullptr) continue;

		for (Entity* const other : findNearestEntities(entity.get()))
		{
			Collider2dComponent* const otherCollider = other->findComponent<Collider2dComponent>();
			if (otherCollider == nullptr) continue;

			collider->collide(*otherCollider);
		}
	}
}

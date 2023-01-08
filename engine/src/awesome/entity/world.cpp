#include "world.h"

#include <thread>

#include <awesome/component/collider2d_component.h>
#include <awesome/core/serialization.h>
#include <awesome/data/json_file.h>

void World::update(const double deltaTime)
{
	if (m_state == State::Loading) return;

	// quadtree update & parenting
	for (const auto& entity : m_entities)
	{
		if (entity->getState() != Entity::State::Alive) continue;

		Collider2dComponent* const collider = entity->findComponent<Collider2dComponent>();
		if (collider != nullptr)
		{
			m_quadspace.insert(entity.get(), 12);
		}
	}

	// sort the entities by depth
	std::sort(m_entities.begin(), m_entities.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) -> bool
		{
			return a->transform.position.z < b->transform.position.z;
		}
	);

	for (const auto& entity : m_entities)
	{
		switch (entity->getState())
		{
		case Entity::State::PendingDestroy: m_pendingDestroyEntities.push_back(entity->getId()); break;
		default: entity->update(deltaTime); break;
		}
	}
	
	checkCollisions();
}

void World::flush()
{
	if (m_state == State::Loading) return;

	for (const uuid& entityToDestroy : m_pendingDestroyEntities)
	{
		const auto& it = std::find_if(m_entities.begin(), m_entities.end(), [entityToDestroy](const std::unique_ptr<Entity>& entity) -> bool
			{
				return entity->getId() == entityToDestroy;
			}
		);

		if (it != m_entities.end())
		{
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

		const auto& entityChildren = entity->findChildrenByTag(tag);
		entities.insert(entities.end(), entityChildren.begin(), entityChildren.end());
	}
	return entities;
}

Entity* const World::findEntityById(const uuid& id) const
{
	for (const auto& entity : m_entities)
	{
		if (entity->getId() == id)
		{
			return entity.get();
		}

		Entity* const child = entity->findChildById(id);
		if (child != nullptr) return child;
	}
	return nullptr;
}

Entity* const World::findEntityByName(const std::string& name) const
{
	for (const auto& entity : m_entities)
	{
		if (entity->name == name)
		{
			return entity.get();
		}

		Entity* const child = entity->findChildByName(name);
		if (child != nullptr) return child;
	}
	return nullptr;
}

Entity* const World::findEntityByTag(const std::string& tag) const
{
	for (const auto& entity : m_entities)
	{
		if (entity->tag == tag)
		{
			return entity.get();
		}

		Entity* const child = entity->findChildByTag(tag);
		if (child != nullptr) return child;
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
	std::vector<std::unique_ptr<Entity>> entitiesToKeep;
	for (auto& entity : m_entities)
	{
		if (entity->persistent)
		{
			entitiesToKeep.push_back(std::move(entity));
		}
	}
	m_entities.clear();
	m_entities = std::move(entitiesToKeep);
	
	m_pendingDestroyEntities.clear();
	m_pendingSpawnEntities.clear();
	m_quadspace.clear();
	m_scene.reset();
}

Entity* const World::instantiate()
{
	return instantiate(math::vec3::zero, math::quaternion::identity);
}

Entity* const World::instantiate(const math::vec3& position)
{
	return instantiate(position, math::quaternion::identity);
}

Entity* const World::instantiate(const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = new Entity();
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	return instantiate(entity);
}

Entity* const World::instantiate(Entity* const entity)
{
	if (entity != nullptr)
	{
		m_pendingSpawnEntities.push_back(std::unique_ptr<Entity>(entity));
	}
	return entity;
}

Entity* const World::instantiate(const PrefabAssetPtr& prefab)
{
	return instantiate(prefab, math::vec3::zero, math::quaternion::identity);
}

Entity* const World::instantiate(const PrefabAssetPtr& prefab, const math::vec3& position)
{
	return instantiate(prefab, position, math::quaternion::identity);
}

Entity* const World::instantiate(const PrefabAssetPtr& prefab, const math::vec3& position, const math::quaternion& quaternion)
{
	Entity* const entity = Entity::load(prefab);
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z;
	return instantiate(entity);
}

void World::load(const SceneAssetPtr& scene)
{
	clear();
	m_loadingProgress = 0;
	m_scene = scene;

	m_state = State::Loading;
	std::thread handler([this]()
		{
			const json::value& data = m_scene->data.value();
			if (data.contains("description")) description = data["description"].as_string();
			if (data.contains("settings")) Deserializer::deserialize(data["settings"], settings);
			if (data.contains("entities"))
			{
				const auto& list = data.at("entities").as_array();
				const size_t count = list.size();
				for (int i = 0; i < count; ++i)
				{
					Entity* entity = nullptr;
					Deserializer::deserialize(list[i], (Type**)&entity, "Entity");
					m_pendingSpawnEntities.push_back(std::unique_ptr<Entity>(entity));

					m_loadingProgress = static_cast<int>((i + 1) * 100 / count);
				}
			}
			m_state = State::Ready;
		}
	);
	handler.detach();
}

void World::save(const std::filesystem::path& path)
{
	json::value entities = json::array();
	for (const auto& entity : m_entities)
	{
		if (entity->transient) continue;

		entities.push_back(Serializer::serialize(*entity.get()));
	}

	JsonFile::save(json::object(
		{
			{"description", description},
			{"entities", entities},
			{"settings", Serializer::serialize(settings)}
		}), 
		path
	);
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

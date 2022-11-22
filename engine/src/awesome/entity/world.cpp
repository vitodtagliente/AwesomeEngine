#include "world.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/component/collider2d_component.h>
#include <awesome/data/archive.h>
#include <awesome/graphics/renderer.h>
#include <awesome/net/network_manager.h>

void World::update(const double deltaTime, const int quadspaceBounds)
{
	for (const auto& entity : m_entities)
	{
		entity->update(deltaTime);

		Collider2dComponent* const collider = entity->findComponent<Collider2dComponent>();
		if (collider != nullptr)
		{
			m_quadspace.insert(entity.get(), quadspaceBounds);
		}
	}

	m_sceneLoader.update(deltaTime);
	checkCollisions();
}

void World::render(graphics::Renderer2D* const renderer, const bool drawWireframes, const graphics::Color& wireframesColor)
{
	// sort the entities by z
	std::sort(m_entities.begin(), m_entities.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) -> bool
		{
			return a->transform.position.z < b->transform.position.z;
		}
	);

	for (const auto& entity : m_entities)
	{
		entity->render(renderer);
	}

	if (drawWireframes)
	{
		m_quadspace.render(renderer, wireframesColor);
	}
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
	std::vector<Entity*> entities = findNearestEntities(entity);
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

std::vector<Entity*> World::findNearestEntities(Entity* const entity) const
{
	return m_quadspace.retrieve(entity);
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
	if (!net::NetworkManager::instance().hasNetworkAuthority()) return nullptr;

	Entity* const entity = new Entity();
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	entity->prepareToSpawn();
	m_pendingSpawnEntities.push_back(std::unique_ptr<Entity>(entity));

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
	if (!net::NetworkManager::instance().hasNetworkAuthority()) return nullptr;

	Entity* const entity = new Entity();
	Entity::duplicate(prefab, *entity);
	entity->transform.position = position;
	entity->transform.rotation.z = quaternion.z; // 2d only
	entity->prepareToSpawn();
	m_pendingSpawnEntities.push_back(std::unique_ptr<Entity>(entity));

	return entity;
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
	if (m_sceneLoader.isLoading())
	{
		return progress = m_sceneLoader.getProgress(), true;
	}
	return progress = 0, false;
}

void World::load(const SceneAssetPtr& scene)
{
	m_loadedSceneId = scene->descriptor.id;

	clear();

	m_sceneLoader.load(scene, [this](std::vector<std::unique_ptr<Entity>>& entities) -> void
		{
			for (auto& entity : entities)
			{
				entity->prepareToSpawn();
				m_pendingSpawnEntities.push_back(std::move(entity));
			}
		}
	);
}

void World::save(const std::filesystem::path& path)
{
	Archive archive(path, Archive::Mode::Write);
	archive << json::Serializer::to_string(serialize());

	AssetImporter importer;
	importer.import(path, m_loadedSceneId);
}

json::value World::serialize() const
{
	json::value data = json::object();
	{
		json::value entities = json::array();
		for (const auto& entity : m_entities)
		{
			entities.push_back(entity->serialize());
		}
		data["entities"] = entities;
	}
	return data;
}

json::value World::netSerialize() const
{
	json::value data = json::object();
	{
		json::value entities = json::array();
		for (const auto& entity : m_entities)
		{
			if (entity && entity->replicate)
			{
				entities.push_back(entity->serialize());
			}
		}
		data["entities"] = entities;
	}
	return data;
}

void World::netDeserialize(const json::value& value)
{
	const auto& jsonEntities = value.safeAt("entities").as_array({});
	for (const json::value& jsonEntity : jsonEntities)
	{
		uuid entityId = uuid::Invalid;
		::deserialize(jsonEntity.safeAt("id"), entityId);

		Entity* entity = findEntityById(entityId);
		if (entity != nullptr)
		{
			entity->deserialize(jsonEntity);
		}
		else
		{
			// net spawn
			std::unique_ptr<Entity> netEntity = std::make_unique<Entity>();
			netEntity->deserialize(jsonEntity);
			m_pendingSpawnEntities.push_back(std::move(netEntity));
		}
	}
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

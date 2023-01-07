/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include <awesome/asset/scene_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>
#include <awesome/math/quaternion.h>
#include <awesome/math/transform.h>

#include "entity.h"
#include "quadspace.h"

#include "world_generated.h"

CLASS(Type = World)
class World final : public Type, public Singleton<World>
{
public:
	enum class State
	{
		Loading,
		Ready
	};

	void clear();
	void flush();
	void update(double deltaTime);

	inline const std::vector<std::unique_ptr<Entity>>& getEntities() const { return m_entities; }
	inline const Quadspace& getQuadspace() const { return m_quadspace; }
	inline const SceneAssetPtr& getScene() const { return m_scene; }
	inline State getState() const { return m_state; }

	std::vector<Entity*> findEntitiesByTag(const std::string& tag) const;
	Entity* const findEntityById(const uuid& id) const;
	Entity* const findEntityByName(const std::string& name) const;
	Entity* const findEntityByTag(const std::string& tag) const;

	Entity* const findNearestEntity(Entity* const entity) const;
	Entity* const findNearestEntityByTag(Entity* const entity, const std::string& tag) const;
	std::vector<Entity*> findNearestEntities(Entity* const entity) const;
	std::vector<Entity*> findNearestEntities(Entity* const entity, float distance) const;
	std::vector<Entity*> findNearestEntitiesByTag(Entity* const entity, const std::string& tag) const;
	std::vector<Entity*> findNearestEntitiesByTag(Entity* const entity, float distance, const std::string& tag) const;

	Entity* const instantiate();
	Entity* const instantiate(const math::vec3& position);
	Entity* const instantiate(const math::vec3& position, const math::quaternion& quaternion);
	Entity* const instantiate(Entity* const entity);
	template <typename T = Entity>
	T* const instantiate()
	{
		return instantiate(new T());
	}
	Entity* const instantiate(const PrefabAssetPtr& prefab);
	Entity* const instantiate(const PrefabAssetPtr& prefab, const math::vec3& position);
	Entity* const instantiate(const PrefabAssetPtr& prefab, const math::vec3& position, const math::quaternion& quaternion);

	void load(const SceneAssetPtr& scene);
	void save(const std::filesystem::path& path);

	GENERATED_BODY()

private:
	void checkCollisions();

	PROPERTY() std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<uuid> m_pendingDestroyEntities; 
	std::vector<std::unique_ptr<Entity>> m_pendingSpawnEntities;
	SceneAssetPtr m_scene;
	State m_state{ State::Ready };
	Quadspace m_quadspace;
};
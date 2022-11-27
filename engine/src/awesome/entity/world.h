/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include <awesome/asset/prefab_asset.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/core/serialization.h>
#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>
#include <awesome/graphics/color.h>
#include <awesome/entity/private/scene_loader.h>
#include <awesome/math/quaternion.h>
#include <awesome/math/vector3.h>

#include "entity.h"
#include "quadspace.h"

namespace graphics
{
	class Renderer2D;
}

class World final : public Singleton<World>, ISerializable
{
public:
	World() = default;
	~World() = default;

	void update(double deltaTime, int quadspaceBounds);
	void render(graphics::Renderer2D* const renderer, bool drawWireframes, const graphics::Color& wireframesColor);
	void flush();

	inline const std::vector<std::unique_ptr<Entity>>& getEntities() const { return m_entities; }
	inline const Quadspace& getQuadspace() const { return m_quadspace; }
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
	inline const uuid& getLoadedSceneId() const { return m_loadedSceneId; }

	Entity* const spawn();
	Entity* const spawn(const math::vec3& position);
	Entity* const spawn(const math::vec3& position, const math::quaternion& quaternion);
	Entity* const spawn(const PrefabAssetPtr& prefab);
	Entity* const spawn(const PrefabAssetPtr& prefab, const math::vec3& position);
	Entity* const spawn(const PrefabAssetPtr& prefab, const math::vec3& position, const math::quaternion& quaternion);

	void destroy(Entity* const entity);
	void destroy(const uuid& id);

	void clear();

	bool isLoading(size_t& progress) const;
	void load(const SceneAssetPtr& scene);
	void save(const std::filesystem::path& path);

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value&) override {};

	json::value netSerialize() const;
	void netDeserialize(const json::value&);

private:
	void checkCollisions();

	std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<std::unique_ptr<Entity>> m_pendingSpawnEntities;
	std::vector<uuid> m_pendingDestroyEntities;
	uuid m_loadedSceneId{ uuid::Invalid };
	Quadspace m_quadspace;
	SceneLoader m_sceneLoader;
};
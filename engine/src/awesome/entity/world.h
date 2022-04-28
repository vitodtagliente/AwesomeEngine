/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include <awesome/core/serialization.h>
#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/entity/private/scene_loader.h>
#include <awesome/math/quaternion.h>
#include <awesome/math/vector3.h>

#include "entity.h"

class Renderer;

namespace graphics
{
	class Renderer;
}

class World final : public Singleton<World>, ISerializable
{
public:
	World() = default;
	~World() = default;

	void update(double deltaTime);
	void render(graphics::Renderer* const renderer);
	void flush();

	inline const std::vector<std::unique_ptr<Entity>>& getEntities() const { return m_entities; }
	std::vector<Entity*> findEntitiesByTag(const std::string& tag) const;
	Entity* const findEntityById(const uuid& id) const;
	Entity* const findEntityByName(const std::string& name) const;
	inline const uuid& getSceneId() const { return m_sceneId; }

	Entity* const spawn();
	Entity* const spawn(const vec3& position);
	Entity* const spawn(const vec3& position, const quaternion& quaternion);

	void destroy(Entity* const entity);
	void destroy(const uuid& id);

	void clear();

	void load(const SceneAssetPtr& scene);
	bool isLoading(size_t& progress) const;

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value&) override {};

private:

	std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<std::unique_ptr<Entity>> m_pendingSpawnEntities;
	std::vector<uuid> m_pendingDestroyEntities;
	uuid m_sceneId{ uuid::Invalid };
	SceneLoader m_sceneLoader;
};
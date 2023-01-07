/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include <awesome/asset/scene_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/singleton.h>

#include "quadspace.h"

#include "world_generated.h"

class Entity;

CLASS(Type = World)
class World final : public Singleton<World>, public Entity
{
public:
	void clear();
	void flush();
	virtual void update(double deltaTime) override;

	inline const Quadspace& getQuadspace() const { return m_quadspace; }
	inline const SceneAssetPtr& getScene() const { return m_scene; }

	Entity* const findNearestEntity(Entity* const entity) const;
	Entity* const findNearestEntityByTag(Entity* const entity, const std::string& tag) const;
	std::vector<Entity*> findNearestEntities(Entity* const entity) const;
	std::vector<Entity*> findNearestEntities(Entity* const entity, float distance) const;
	std::vector<Entity*> findNearestEntitiesByTag(Entity* const entity, const std::string& tag) const;
	std::vector<Entity*> findNearestEntitiesByTag(Entity* const entity, float distance, const std::string& tag) const;

	void load(const SceneAssetPtr& scene);
	void save(const std::filesystem::path& path);

	GENERATED_BODY()

private:
	void checkCollisions();

	SceneAssetPtr m_scene;
	Quadspace m_quadspace;
};
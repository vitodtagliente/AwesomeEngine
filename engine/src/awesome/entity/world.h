/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>
#include <awesome/math/quaternion.h>
#include <awesome/math/vector3.h>

#include "entity.h"

class Renderer;

namespace graphics
{
	class Renderer;
}

class World : public Singleton<World>
{
public:

	World() = default;
	~World() = default;

	void update(double deltaTime);
	void render(graphics::Renderer* const renderer);
	void flush();

	inline const std::vector<EntityPtr>& getEntities() const { return m_entities; }
	std::vector<EntityPtr> findEntitiesByTag(const std::string& tag) const;
	EntityPtr const findEntityById(const uuid& id) const;
	EntityPtr const findEntityByName(const std::string& name) const;

	EntityPtr const spawn();
	EntityPtr const spawn(const vec3& position);
	EntityPtr const spawn(const vec3& position, const quaternion& quaternion);
	EntityPtr const spawn(const Entity& prefab);
	EntityPtr const spawn(const Entity& prefab, const vec3& position);
	EntityPtr const spawn(const Entity& prefab, const vec3& position, const quaternion& quaternion);
	void destroy(const EntityPtr& entity);

	void clear();

private:

	std::vector<EntityPtr> m_entities;
	std::vector<EntityPtr> m_pendingSpawnEntities;
	std::vector<EntityPtr> m_pendingDestroyEntities;

};
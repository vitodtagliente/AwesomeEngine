/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/singleton.h>
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

	World();
	~World();

	void update(double deltaTime);
	void render(graphics::Renderer* const renderer);
	void flush();

	inline const std::vector<Entity*>& getEntities() const { return m_entities; }
	std::vector<Entity*> findEntitiesByTag(const std::string& tag) const;
	Entity* const findEntityByName(const std::string& name) const;

	Entity* const spawn();
	Entity* const spawn(const vec3& position);
	Entity* const spawn(const vec3& position, const quaternion& quaternion);
	Entity* const spawn(const Entity& prefab);
	Entity* const spawn(const Entity& prefab, const vec3& position);
	Entity* const spawn(const Entity& prefab, const vec3& position, const quaternion& quaternion);
	void destroy(Entity* const entity);

	void clear();

private:

	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_pendingSpawnEntities;
	std::vector<Entity*> m_pendingDestroyEntities;

};
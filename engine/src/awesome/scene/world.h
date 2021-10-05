/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/singleton.h>
#include <vdtmath/quaternion.h>
#include <vdtmath/vector3.h>

class Entity;

class World : public Singleton<World>
{
public:

	World();
	~World() = default;

	void update(double deltaTime);
	void render();

	inline const std::vector<Entity*>& getEntities() const { return m_entities; }

	Entity* const spawn(const math::vec3& position, const math::quaternion& quaternion);
	void destroy(Entity* const entity);

private:

	std::vector<Entity*> m_entities;

};
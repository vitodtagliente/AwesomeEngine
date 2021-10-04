/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/quaternion.h>
#include <vdtmath/vector3.h>

class Entity;

class World
{
public:

	World();
	~World() = default;

	void update(double deltaTime);
	void render();

	Entity* const spawn(const math::vec3& position, const math::quaternion& quaternion);
	void destroy(Entity* const entity);

private:

	std::vector<Entity*> m_entities;

};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/entity/entity.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

class Quadspace
{
public:
	Quadspace(int bounds);

	std::vector<Entity*> retrieve(Entity* const entity) const;
	void clear();
	void insert(Entity* const entity);

private:
	void insertNewSpace(Entity* const entity);
	int getIndex(const math::vec3& position) const;

	struct Space
	{
		Space() = default;

		std::vector<Entity*> entities;
		math::vec3 position;
		int bounds;

		void clear();
	};

	std::vector<Space> m_spaces;
	int m_bounds;
};
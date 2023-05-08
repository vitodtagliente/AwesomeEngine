/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

class Entity;

class QuadTree
{
public:
	struct Settings
	{
		int maxDepth{ 4 };
		int threshold{ 20 };
	};

	QuadTree() = default;
	QuadTree(const math::vec3& position, const math::vec2& boundary);

	bool isLeaf()const { return m_children.empty(); }

	void clear();
	bool insert(Entity* const entity);
	std::vector<Entity*> query(const math::vec3& position, const math::vec2& boundary) const;

	Settings settings;

private:
	bool query(const math::vec3& position, const math::vec2& boundary, std::vector<Entity*>& entities) const;
	void subdivide();
	void updatePosition();

	math::vec2 m_boundary{ 1.f, 1.f };
	int m_capacity{ 1 };
	std::vector<QuadTree> m_children;
	int m_depth{ 0 };
	std::vector<Entity*> m_entities;
	math::vec3 m_position{ 0.f, 0.f, 0.f };
};
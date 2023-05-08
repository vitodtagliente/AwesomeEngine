/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

class Entity;

namespace graphics
{
	class Renderer;
}

class QuadTreeNode
{
public:
	QuadTreeNode() = default;
	QuadTreeNode(const math::vec3& position, const math::vec2& boundary);

	bool isLeaf() const { return m_children.empty(); }

	void clear();
	void clear(const math::vec3& position, const math::vec2& boundary);
	bool insert(Entity* const entity);
	std::vector<Entity*> query(const math::vec3& position, const math::vec2& boundary) const;
	void render(graphics::Renderer& renderer) const;

	int threshold{ 20 };

private:
	bool query(const math::vec3& position, const math::vec2& boundary, std::vector<Entity*>& entities) const;
	void subdivide();

	math::vec2 m_boundary{ 1.f, 1.f };
	int m_capacity{ 1 };
	std::vector<QuadTreeNode> m_children;
	int m_depth{ 0 };
	std::vector<Entity*> m_entities;
	math::vec3 m_position{ 0.f, 0.f, 0.f };
};

typedef QuadTreeNode QuadTree;
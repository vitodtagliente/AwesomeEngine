/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/math/rectangle.h>
#include <awesome/math/vector2.h>

class Entity;

namespace graphics
{
	class Renderer;
}

class QuadTreeNode
{
public:
	QuadTreeNode() = default;
	QuadTreeNode(const math::rect& aabb);

	bool isLeaf() const { return m_children.empty(); }

	void clear();
	bool insert(Entity* const entity);
	std::vector<Entity*> query(const math::rect& aabb) const;
	void render(graphics::Renderer& renderer) const;

	int capacity{ 4 };
	int threshold{ 20 };

private:
	bool query(const math::rect& aabb, std::vector<Entity*>& entities) const;
	void subdivide();

	math::rect m_aabb{ 0.f, 0.f, 50.f, 50.f };
	std::vector<QuadTreeNode> m_children;
	int m_depth{ 0 };
	std::vector<Entity*> m_entities;
};

class QuadTree : public QuadTreeNode, public Singleton<QuadTree>
{
public:
	QuadTree() = default;
};
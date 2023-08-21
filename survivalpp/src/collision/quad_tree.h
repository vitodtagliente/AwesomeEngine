/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include "ecs/component_ptr.h"

#include "core/singleton.h"
#include "graphics/color.h"
#include "graphics/renderer.h"
#include "math/rectangle.h"
#include "math/vector2.h"

#include "components/rigidbody2d.h"

class QuadTreeNode
{
public:
	QuadTreeNode() = default;
	QuadTreeNode(const math::rect& aabb);

	bool isLeaf() const { return m_children.empty(); }

	void clear();
	bool insert(const ComponentPtr<Rigidbody2D>& body);
	std::vector<ComponentPtr<Rigidbody2D>> query(const math::rect& aabb) const;
	void render(graphics::Renderer& renderer, const graphics::Color& color = graphics::Color::Black) const;

	int capacity{ 4 };
	int threshold{ 20 };

private:
	bool query(const math::rect& aabb, std::vector<ComponentPtr<Rigidbody2D>>& m_bodies) const;
	void subdivide();

	math::rect m_aabb{ 0.f, 0.f, 0.f, 0.f };
	std::vector<QuadTreeNode> m_children;
	int m_depth{ 0 };
	std::vector<ComponentPtr<Rigidbody2D>> m_bodies;
	math::vec2 m_maxBounds{ 0.f, 0.f };
};

class QuadTree : public QuadTreeNode, public Singleton<QuadTree>
{
public:
	QuadTree() = default;
};
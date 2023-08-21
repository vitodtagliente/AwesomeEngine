#include "quad_tree.h"

#include "ecs/entity.h"

enum Direction : int
{
	First = 0,
	NorthWest = 0,
	NorthEast = 1,
	SouthWest = 2,
	SouthEast = 3,
	Count
};

QuadTreeNode::QuadTreeNode(const math::rect& aabb)
	: m_aabb(aabb)
{
}

/**
 * Clear the quadtree
 */
void QuadTreeNode::clear()
{
	m_children.clear();
	m_bodies.clear();
	m_aabb.width = m_maxBounds.x;
	m_aabb.height = m_maxBounds.y;
}

/**
 * Insert the entity into the quadtree
 * @param entity The entity
 */
bool QuadTreeNode::insert(const ComponentPtr<Rigidbody2D>& body)
{
	if (!m_aabb.contains(body->entity()->transform.position))
	{
		m_maxBounds.x = std::max(m_maxBounds.x, std::abs(body->entity()->transform.position.x) + 1.f);
		m_maxBounds.y = std::max(m_maxBounds.y, std::abs(body->entity()->transform.position.y) + 1.f);
		return false;
	}

	if (m_bodies.size() < capacity)
	{
		m_bodies.push_back(body);
		return true;
	}
	else
	{
		if (m_children.empty())
		{
			subdivide();
		}

		return m_children[Direction::NorthEast].insert(body)
			|| m_children[Direction::NorthWest].insert(body)
			|| m_children[Direction::SouthEast].insert(body)
			|| m_children[Direction::SouthWest].insert(body);
	}
}

std::vector<ComponentPtr<Rigidbody2D>> QuadTreeNode::query(const math::rect& aabb) const
{
	std::vector<ComponentPtr<Rigidbody2D>> result;
	query(aabb, result);
	return result;
}

void QuadTreeNode::render(graphics::Renderer& renderer, const graphics::Color& color) const
{
	for (const QuadTreeNode& child : m_children)
	{
		child.render(renderer, color);
	}
	renderer.submitDrawRect(graphics::ShapeRenderStyle::stroke, math::vec2(m_aabb.x, m_aabb.y), m_aabb.width * 2, m_aabb.height * 2, color);
}

/**
 * Retrieve the list of entities near to the specified one
 * @param entity The entity to surround
 */
bool QuadTreeNode::query(const math::rect& aabb, std::vector<ComponentPtr<Rigidbody2D>>& entities) const
{
	std::vector<ComponentPtr<Rigidbody2D>> result;
	if (!m_aabb.intersects(aabb))
		return false;

	for (const ComponentPtr<Rigidbody2D>& body : m_bodies)
	{
		if (m_aabb.contains(body->entity()->transform.position))
		{
			entities.push_back(body);
		}
	}

	if (!m_children.empty())
	{
		m_children[Direction::NorthEast].query(aabb, entities);
		m_children[Direction::NorthWest].query(aabb, entities);
		m_children[Direction::SouthEast].query(aabb, entities);
		m_children[Direction::SouthWest].query(aabb, entities);
	}

	return true;
}

void QuadTreeNode::subdivide()
{
	m_children.reserve(4);
	const math::vec2& bounds{ m_aabb.width / 2, m_aabb.height / 2 };
	m_children.push_back(QuadTreeNode(math::rect(m_aabb.x + bounds.x, m_aabb.y + bounds.y, bounds.x, bounds.y)));
	m_children.back().capacity = capacity;
	m_children.back().threshold = threshold;
	m_children.push_back(QuadTreeNode(math::rect(m_aabb.x - bounds.x, m_aabb.y + bounds.y, bounds.x, bounds.y)));
	m_children.back().capacity = capacity;
	m_children.back().threshold = threshold;
	m_children.push_back(QuadTreeNode(math::rect(m_aabb.x + bounds.x, m_aabb.y - bounds.y, bounds.x, bounds.y)));
	m_children.back().capacity = capacity;
	m_children.back().threshold = threshold;
	m_children.push_back(QuadTreeNode(math::rect(m_aabb.x - bounds.x, m_aabb.y - bounds.y, bounds.x, bounds.y)));
	m_children.back().capacity = capacity;
	m_children.back().threshold = threshold;
}
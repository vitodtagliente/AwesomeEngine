#include "quad_tree.h"

#include <awesome/graphics/renderer.h>
#include <awesome/scene/entity.h>

enum Direction : int
{
	First = 0,
	NorthWest = 0,
	NorthEast = 1,
	SouthWest = 2,
	SouthEast = 3,
	Count
};

math::vec2 to_vec2(const math::vec3& v)
{
	return math::vec2(v.x, v.y);
}

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
	m_entities.clear();
}

/**
 * Insert the entity into the quadtree
 * @param entity The entity
 */
bool QuadTreeNode::insert(Entity* const entity)
{
	if (!m_aabb.contains(to_vec2(entity->transform.position)))
		return false;

	if (m_entities.size() < capacity)
	{
		m_entities.push_back(entity);
		return true;
	}
	else
	{
		if (m_children.empty())
		{
			subdivide();
		}

		return m_children[Direction::NorthEast].insert(entity)
			|| m_children[Direction::NorthWest].insert(entity)
			|| m_children[Direction::SouthEast].insert(entity)
			|| m_children[Direction::SouthWest].insert(entity);
	}
}

std::vector<Entity*> QuadTreeNode::query(const math::rect& aabb) const
{
	std::vector<Entity*> result;
	query(aabb, result);
	return result;
}

void QuadTreeNode::render(graphics::Renderer& renderer) const
{
	for (const QuadTreeNode& child : m_children)
	{
		child.render(renderer);
	}
	renderer.submitDrawRect(graphics::ShapeRenderStyle::stroke, math::vec3(m_aabb.x, m_aabb.y, 0.f), m_aabb.width * 2, m_aabb.height * 2, graphics::Color::Black);
}

/**
 * Retrieve the list of entities near to the specified one
 * @param entity The entity to surround
 */
bool QuadTreeNode::query(const math::rect& aabb, std::vector<Entity*>& entities) const
{
	std::vector<Entity*> result;
	if (!m_aabb.intersects(aabb))
		return false;

	for (Entity* const entity : m_entities)
	{
		if (m_aabb.contains(to_vec2(entity->transform.position)))
		{
			entities.push_back(entity);
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
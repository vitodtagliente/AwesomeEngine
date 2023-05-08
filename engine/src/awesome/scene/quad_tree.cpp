#include "quad_tree.h"

#include <awesome/graphics/renderer.h>

#include "entity.h"

enum Direction : int
{
	First = 0,
	NorthWest = 0,
	NorthEast = 1,
	SouthWest = 2,
	SouthEast = 3,
	Count
};

bool contains( const math::vec3& position, const math::vec2& boundary, Entity* const entity)
{
	const math::vec3& entity_position = entity->transform.position;
	return entity_position.x >= position.x - boundary.x
		&& entity_position.x <= position.x + boundary.x
		&& entity_position.y >= position.y - boundary.y
		&& entity_position.y <= position.y + boundary.y;
}

bool intersects(const math::vec3& pos1, const math::vec2& boundary1,
	const math::vec3& pos2, const math::vec2& boundary2)
{
	return !(pos2.x - boundary2.x > pos1.x + boundary1.x
		|| pos2.x + boundary2.x < pos1.x - boundary1.x
		|| pos2.y - boundary2.y > pos1.y + boundary1.y
		|| pos2.y + boundary2.y > pos1.y - boundary1.y);
}

QuadTreeNode::QuadTreeNode(const math::vec3& position, const math::vec2& boundary)
	: m_boundary(boundary)
	, m_position(position)
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

void QuadTreeNode::clear(const math::vec3& position, const math::vec2& boundary)
{
	m_children.clear();
	m_entities.clear();

	m_position = position;
	m_boundary = boundary;
}

/**
 * Insert the entity into the quadtree
 * @param entity The entity
 */
bool QuadTreeNode::insert(Entity* const entity)
{
	if (!contains(m_position, m_boundary, entity))
		return false;

	if (m_entities.size() < m_capacity)
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

std::vector<Entity*> QuadTreeNode::query(const math::vec3& position, const math::vec2& boundary) const
{
	std::vector<Entity*> result;
	query(position, boundary, result);
	return result;
}

void QuadTreeNode::render(graphics::Renderer& renderer) const
{
	for (const QuadTreeNode& child : m_children)
	{
		child.render(renderer);
	}
	for (Entity* const entity : m_entities)
	{
		renderer.submitDrawCircle(graphics::ShapeRenderStyle::stroke, entity->transform.position, 1.f, graphics::Color::Black);
	}
	renderer.submitDrawRect(graphics::ShapeRenderStyle::stroke, m_position, m_boundary.x, m_boundary.y, graphics::Color::Black);
}

/**
 * Retrieve the list of entities near to the specified one
 * @param entity The entity to surround
 */
bool QuadTreeNode::query(const math::vec3& position, const math::vec2& boundary, std::vector<Entity*>& entities) const
{
	std::vector<Entity*> result;
	if (!intersects(m_position, m_boundary, position, boundary))
		return false;

	for (Entity* const entity : m_entities)
	{
		if (contains(m_position, m_boundary, entity))
		{
			entities.push_back(entity);
		}
	}

	if (!m_children.empty())
	{
		m_children[Direction::NorthEast].query(position, boundary, entities);
		m_children[Direction::NorthWest].query(position, boundary, entities);
		m_children[Direction::SouthEast].query(position, boundary, entities);
		m_children[Direction::SouthWest].query(position, boundary, entities);
	}

	return true;
}

void QuadTreeNode::subdivide()
{
	m_children.reserve(4);
	const math::vec2 new_boundary = m_boundary / 2;
	const math::vec2 new_boundary2 = new_boundary / 2;
	m_children.push_back(QuadTreeNode(math::vec3(m_position.x + new_boundary2.x, m_position.y - new_boundary2.y, 0.f), new_boundary));
	m_children.back().threshold = threshold;
	m_children.push_back(QuadTreeNode(math::vec3(m_position.x - new_boundary2.x, m_position.y - new_boundary2.y, 0.f), new_boundary));
	m_children.back().threshold = threshold;
	m_children.push_back(QuadTreeNode(math::vec3(m_position.x + new_boundary2.x, m_position.y + new_boundary2.y, 0.f), new_boundary));
	m_children.back().threshold = threshold;
	m_children.push_back(QuadTreeNode(math::vec3(m_position.x - new_boundary2.x, m_position.y + new_boundary2.y, 0.f), new_boundary));
	m_children.back().threshold = threshold;
}
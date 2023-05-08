#include "quad_tree.h"

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

QuadTree::QuadTree(const math::vec3& position, const math::vec2& boundary)
	: m_boundary(boundary)
	, m_position(position)
{
}

/**
 * Clear the quadtree
 */
void QuadTree::clear()
{

}

/**
 * Insert the entity into the quadtree
 * @param entity The entity
 */
bool QuadTree::insert(Entity* const entity)
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

std::vector<Entity*> QuadTree::query(const math::vec3& position, const math::vec2& boundary) const
{
	std::vector<Entity*> result;
	query(position, boundary, result);
	return result;
}

/**
 * Retrieve the list of entities near to the specified one
 * @param entity The entity to surround
 */
bool QuadTree::query(const math::vec3& position, const math::vec2& boundary, std::vector<Entity*>& entities) const
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

void QuadTree::subdivide()
{
	m_children.reserve(4);
	const math::vec2 new_boundary = m_boundary / 2;
	m_children.push_back(QuadTree(math::vec3(m_position.x + new_boundary.x, m_position.y - new_boundary.y, 0.f), new_boundary));
	m_children.push_back(QuadTree(math::vec3(m_position.x - new_boundary.x, m_position.y - new_boundary.y, 0.f), new_boundary));
	m_children.push_back(QuadTree(math::vec3(m_position.x + new_boundary.x, m_position.y + new_boundary.y, 0.f), new_boundary));
	m_children.push_back(QuadTree(math::vec3(m_position.x - new_boundary.x, m_position.y + new_boundary.y, 0.f), new_boundary));
}

void QuadTree::updatePosition()
{
	m_position = math::vec3::zero;
	for (const Entity* entity : m_entities)
	{
		m_position += entity->transform.position;
	}
	m_position /= m_entities.size();
}
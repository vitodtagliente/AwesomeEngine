#include "quad_tree.h"

#include "entity.h"

void QuadTree::Space::clear()
{
	entities.clear();
}

/**
 * Retrieve the list of entities near to the specified one
 * @param entity The entity to surround
 */
std::vector<Entity*> QuadTree::retrieve(Entity* const entity) const
{
	std::vector<Entity*> result;
	const int index = getIndex(entity->transform.position);
	if (index >= 0)
	{
		for (Entity* const e : m_spaces[index].entities)
		{
			if (e->id() != entity->id())
			{
				result.push_back(e);
			}
		}
	}
	return result;
}

/**
 * Clear the quadtree
 */
void QuadTree::clear()
{
	m_spaces.clear();
}

/**
 * Insert the entity into the quadtree
 * @param entity The entity
 */
void QuadTree::insert(Entity* const entity, const int bounds)
{
	const int index = getIndex(entity->transform.position);
	if (index >= 0)
	{
		m_spaces[index].entities.push_back(entity);
	}
	else
	{
		insertNewSpace(entity, bounds);
	}
}

/**
 * Insert a new space and entity
 * @param entity The entity
 */
void QuadTree::insertNewSpace(Entity* const entity, const int bounds)
{
	Space space;
	space.entities.push_back(entity);
	space.position = entity->transform.position;
	space.bounds = bounds;
	m_spaces.push_back(space);
}

/**
 * Find the space for the entity
 */
int QuadTree::getIndex(const math::vec3& position) const
{
	for (int i = 0; i < m_spaces.size(); ++i)
	{
		const Space& space = m_spaces[i];
		if (position.distance(space.position) <= space.bounds)
		{
			return i;
		}
	}
	return -1;
}
#include "quadspace.h"

#include <awesome/graphics/renderer.h>

void Quadspace::Space::clear()
{
	entities.clear();
}

/**
 * Retrieve the list of entities near to the specified one
 * @param entity The entity to surround
 */
std::vector<Entity*> Quadspace::retrieve(Entity* const entity) const
{
	std::vector<Entity*> result;
	const int index = getIndex(entity->transform.position);
	if (index >= 0)
	{
		for (Entity* const e : m_spaces[index].entities)
		{
			if (e->getId() != entity->getId())
			{
				result.push_back(e);
			}
		}
	}
	return result;
}

void Quadspace::render(graphics::Renderer* const renderer, const graphics::Color& wireframesColor)
{
	for (const Space& space : m_spaces)
	{
		renderer->submitDrawCircle(graphics::ShapeRenderStyle::stroke, space.position, static_cast<float>(space.bounds), wireframesColor);
	}
}

/**
 * Clear the quadspace
 */
void Quadspace::clear()
{
	m_spaces.clear();
}

/**
 * Insert the entity into the quadspace
 * @param entity The entity
 */
void Quadspace::insert(Entity* const entity, const int bounds)
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
void Quadspace::insertNewSpace(Entity* const entity, const int bounds)
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
int Quadspace::getIndex(const math::vec3& position) const
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
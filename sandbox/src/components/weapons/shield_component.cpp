#include "shield_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>

#include "../health_component.h"

void ShiedComponent::init()
{
	m_activationTimer = frequency;
}

void ShiedComponent::render(graphics::Renderer2D* const renderer)
{
	renderer->setPolygonStyle(graphics::PolygonStyle::stroke);
	renderer->drawCircle(getOwner()->transform.position, range, m_color); 
	renderer->setPolygonStyle(graphics::PolygonStyle::fill);
}

void ShiedComponent::update(const double deltaTime)
{
	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		activate();
		m_activationTimer = frequency;
	}
}

void ShiedComponent::activate()
{
	const std::vector<Entity*>& entities = World::instance().findNearestEntities(getOwner(), range);
	for (Entity* const entity : entities)
	{
		HealthComponent* const health = entity->findComponent<HealthComponent>();
		if (health)
		{
			(*health) -= power;
		}
	}
}
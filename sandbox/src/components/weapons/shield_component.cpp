#include "shield_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>

#include <components/health_component.h>
#include <game_tags.h>

void ShieldComponent::init()
{
	WeaponComponent::init();
}

void ShieldComponent::render(graphics::Renderer2D* const renderer)
{
	renderer->setPolygonStyle(graphics::PolygonStyle::stroke);
	renderer->drawCircle(getOwner()->transform.position, range, m_color); 
	renderer->setPolygonStyle(graphics::PolygonStyle::fill);
}

void ShieldComponent::update(const double deltaTime)
{
	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		activate();
		m_activationTimer = frequency;
	}
}

void ShieldComponent::activate()
{
	const std::vector<Entity*>& entities = World::instance().findNearestEntitiesByTag(getOwner(), range, enumToString(GameTags::Minion));
	for (Entity* const entity : entities)
	{
		HealthComponent* const health = entity->findComponent<HealthComponent>();
		if (health)
		{
			(*health) -= static_cast<int>(efficacy);
		}
	}
}
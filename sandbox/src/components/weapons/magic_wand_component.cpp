#include "magic_wand_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "../../game_tags.h"
#include "../bullet_component.h"

void MagicWandComponent::init()
{
	m_activationTimer = frequency;
	enabled = m_bulletPrefab != nullptr;
}

void MagicWandComponent::update(const double deltaTime)
{
	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		activate();
		m_activationTimer = frequency;
	}
}

void MagicWandComponent::activate()
{
	World& world = World::instance();

	Entity* const nearestEntity = world.findNearestEntityByTag(getOwner(), enumToString(GameTags::Mininon));
	if (nearestEntity == nullptr) return;

	Entity* const bulletEntity = world.spawn(m_bulletPrefab, getOwner()->transform.position);
	BulletComponent* const bulletComponent = bulletEntity->findComponent<BulletComponent>();
	if (bulletComponent)
	{
		bulletComponent->shoot(nearestEntity);
	}
	else
	{
		world.destroy(bulletEntity);
	}
}
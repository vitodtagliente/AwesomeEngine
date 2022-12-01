#include "magic_wand_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "../../game_tags.h"
#include "../bullet_component.h"

void MagicWandComponent::init()
{
	WeaponComponent::init();
}

void MagicWandComponent::update(const double deltaTime)
{
	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		if (m_bulletPrefab != nullptr)
		{
			activate();
		}
		m_activationTimer = frequency;
	}
}

void MagicWandComponent::activate()
{
	World& world = World::instance();

	Entity* const nearestEntity = world.findNearestEntityByTag(getOwner(), enumToString(GameTags::Minion));
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
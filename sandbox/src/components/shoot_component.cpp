#include "shoot_component.h"

#include <awesome/application/input.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include <game_tags.h>
#include <components/aim_component.h>
#include <components/bullet_component.h>

void ShootComponent::init()
{
	m_aim = getOwner()->findComponent<AimComponent>();
}

void ShootComponent::update(const double deltaTime)
{
	Input& input = Input::instance();

	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0 && input.isKeyDown(KeyCode::MouseLeftButton))
	{
		if (m_bulletPrefab != nullptr && m_aim != nullptr)
		{
			shoot();
		}
		m_activationTimer = m_frequency;
	}
}

void ShootComponent::shoot()
{
	World& world = World::instance();

	Entity* const bulletEntity = world.instantiate(m_bulletPrefab, m_aim->getPosition());
	BulletComponent* const bulletComponent = bulletEntity->findComponent<BulletComponent>();
	if (bulletComponent)
	{
		bulletComponent->damage = m_damage;
		bulletComponent->shoot(m_aim->getDirection());
	}
	else
	{
		bulletEntity->queue_destroy();
	}
}

#include "rotating_shields_component.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include <game_tags.h>
#include <components/bullet_component.h>

void RotatingShieldsComponent::init()
{
	WeaponComponent::init();
}

void RotatingShieldsComponent::update(const double deltaTime)
{
	if (m_deactivationTimer > 0)
	{
		m_deactivationTimer -= deltaTime;
		if (m_deactivationTimer <= 0)
		{
			World& world = World::instance();
			for (const auto& [bullet, angle] : m_bullets)
			{
				world.destroy(bullet);
			}
			m_bullets.clear();
		}
	}

	m_activationTimer -= deltaTime;
	if (m_activationTimer <= 0)
	{
		if (m_bulletPrefab != nullptr)
		{
			activate();
			m_deactivationTimer = duration;
		}
		m_activationTimer = frequency;
	}

	const math::vec3& pivot = getOwner()->transform.position;
	for (auto& [bullet, angle] : m_bullets)
	{
		angle += speed * static_cast<float>(deltaTime);
		const math::vec3 offset = math::vec3(std::sin(angle), std::cos(angle), 0.0f) * range;
		bullet->transform.position = pivot + offset;
	}
}

void RotatingShieldsComponent::activate()
{
	World& world = World::instance();
	const math::vec3& pivot = getOwner()->transform.position;

	for (int i = 0; i < quantity; ++i)
	{
		const float angle = i * (math::pi * 2 / quantity);
		const math::vec3 offset = math::vec3(std::sin(angle), std::cos(angle), 0.0f) * range;
		Entity* const bulletEntity = world.spawn(m_bulletPrefab, pivot + offset);
		BulletComponent* const bulletComponent = bulletEntity->findComponent<BulletComponent>();
		if (bulletComponent)
		{
			bulletComponent->damage = static_cast<int>(efficacy);
			m_bullets.push_back(std::make_pair(bulletEntity, angle));
		}
		else
		{
			world.destroy(bulletEntity);
		}
	}
}
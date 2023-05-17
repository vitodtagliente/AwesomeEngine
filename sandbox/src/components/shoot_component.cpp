#include "shoot_component.h"

#include <awesome/engine/input.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

#include "aim_component.h"
#include "bullet_component.h"

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
		if (m_aim != nullptr)
		{
			shoot();
		}
		m_activationTimer = m_frequency;
	}
}

void ShootComponent::shoot()
{
	if (!m_bullet.ready()) return;

	Entity* const entity = SceneGraph::instance().root().addChild(std::make_unique<Entity>(m_bullet.resource->entity));
	entity->transform.position = m_aim->getPosition();
	BulletComponent* const bullet = entity->findComponent<BulletComponent>();
	if (bullet != nullptr)
	{
		bullet->damage = m_damage;
		bullet->shoot(m_aim->getDirection());
	}
	else
	{
		entity->queue_destroy();
	}
}

#include "bullet_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "health_component.h"

void BulletComponent::init()
{
	m_body = getOwner()->findComponent<Body2dComponent>();
	m_collider = getOwner()->findComponent<Collider2dComponent>();
	m_collider->onTrigger.bind([this](const Collider2dComponent& other) -> void
		{
			HealthComponent* health = other.getOwner()->findComponent<HealthComponent>();
			if (health)
			{
				*health -= damage;
				World::instance().destroy(getOwner());
			}
		}
	);
}

void BulletComponent::update(const double deltaTime)
{
	m_body->move(m_direction * m_speed * static_cast<float>(deltaTime));
}

void BulletComponent::shoot(const math::vec3& direction)
{
	m_direction = direction;
}

void BulletComponent::inspect()
{
	Component::inspect();
	Layout::input("Damage", damage);
	Layout::input("Speed", m_speed);
}

json::value BulletComponent::serialize() const
{
	json::value data = Component::serialize();
	data["damage"] = damage;
	data["speed"] = m_speed;
	return data;
}

void BulletComponent::deserialize(const json::value& data)
{
	Component::deserialize(data);
	damage = data.safeAt("damage").as_number(1).as_int();
	m_speed = data.safeAt("speed").as_number(1.f).as_float();
}
#include "bullet.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "health.h"

void Bullet::init()
{
	m_body = getOwner()->findComponent<Body2d>();
	m_collider = getOwner()->findComponent<Collider2d>();
	m_collider->onTrigger = [this](const Collider2d& other) -> void
	{
		Health* health = other.getOwner()->findComponent<Health>();
		if (health)
		{
			*health -= damage;
			World::instance().destroy(getOwner());
		}
	};
}

void Bullet::update(const double deltaTime)
{
	m_body->move(m_direction * m_speed * static_cast<float>(deltaTime));
}

void Bullet::shoot(const math::vec3& direction)
{
	m_direction = direction;
}

void Bullet::inspect()
{
	Component::inspect();
	editor::Layout::input("Damage", damage);
	editor::Layout::input("Speed", m_speed);
}

json::value Bullet::serialize() const
{
	json::value data = Component::serialize();
	data["damage"] = damage;
	data["speed"] = m_speed;
	return data;
}

void Bullet::deserialize(const json::value& data)
{
	Component::deserialize(data);
	damage = data.safeAt("damage").as_number(1).as_int();
	m_speed = data.safeAt("speed").as_number(1.f).as_float();
}

REFLECT_COMPONENT(Bullet)
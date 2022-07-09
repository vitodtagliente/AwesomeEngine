/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/body2d.h>
#include <awesome/component/collider2d.h>
#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

class Bullet : public Component
{
public:
	Bullet() = default;
	virtual ~Bullet() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	void shoot(const math::vec3& direction);

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	int damage{ 1 };

	REFLECT()

private:
	component::Body2d* m_body;
	component::Collider2d* m_collider;
	math::vec3 m_direction;
	float m_speed{ 1.f };
};
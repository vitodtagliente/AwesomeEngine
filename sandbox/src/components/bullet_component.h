/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/body2d_component.h>
#include <awesome/component/collider2d_component.h>

#include "bullet_component_generated.h"

CLASS()
class BulletComponent : public Component
{
public:
	BulletComponent() = default;
	virtual ~BulletComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	void shoot(const math::vec3& direction);

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	int damage{ 1 };

	GENERATED_BODY()

private:
	Body2dComponent* m_body;
	Collider2dComponent* m_collider;
	math::vec3 m_direction;
	float m_speed{ 1.f };
};
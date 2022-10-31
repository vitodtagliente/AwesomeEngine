/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/body2d_component.h>
#include <awesome/component/collider2d_component.h>

#include "bullet_component_generated.h"

CLASS(Category = Component)
class BulletComponent : public Component
{
public:
	BulletComponent() = default;
	virtual ~BulletComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	void shoot(const math::vec3& direction);

	PROPERTY() int damage{ 1 };
	PROPERTY() float speed{ 1.f };

	GENERATED_BODY()

private:
	Body2dComponent* m_body;
	Collider2dComponent* m_collider;
	math::vec3 m_direction;
};
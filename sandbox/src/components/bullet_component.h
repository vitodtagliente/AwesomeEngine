/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/math/vector3.h>
#include <awesome/scene/component.h>

#include "bullet_component_generated.h"

CLASS(Type = Component)
class BulletComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double deltaTime) override;

	void shoot(const math::vec3& direction);
	void shoot(Entity* const entity);

	PROPERTY() int damage{ 1 };
	PROPERTY() float speed{ 1.f };

	GENERATED_BODY()

private:
	class Rigidbody2DComponent* m_body{ nullptr };
	class Collider2DComponent* m_collider{ nullptr };
	PROPERTY() bool m_destroyOnCollision{ true };
	math::vec3 m_direction;
	class Entity* m_target{ nullptr };
	PROPERTY() std::string m_targetTag;
};
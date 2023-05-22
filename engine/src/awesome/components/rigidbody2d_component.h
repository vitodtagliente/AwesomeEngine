/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/ecs/types.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/scene/component.h>

#include "rigidbody2d_component_generated.h"

ENUM()
enum class RigidbodyType2D : int
{
	Dynamic,
	Kinematic,
	Static
};

CLASS(Type = Component)
class Rigidbody2DComponent : public Component
{
public:
	friend class Rigidbody2DComponentInspector;

	Rigidbody2DComponent() = default;
	Rigidbody2DComponent(Rigidbody2DComponent&&) = default;
	Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	Rigidbody2DComponent& operator=(Rigidbody2DComponent&&) = default;

	virtual void init() override;
	virtual void update(double /*deltaTime*/) override;

	const math::vec3& direction() const { return m_direction; }

	void move(const math::vec2& amount);
	void move(const math::vec3& amount);

	PROPERTY() bool freezeRotation{ false };
	PROPERTY() float gravityScale{ 9.8f };
	PROPERTY() float mass{ 1.f };

	GENERATED_BODY()

	ECS_STORAGE_COMPONENT_DECLARE(Rigidbody2DComponent)

private:
	class Collider2DComponent* m_collider{ nullptr };
	math::vec3 m_direction;
	math::vec3 m_lastPosition;
	PROPERTY() RigidbodyType2D m_type { RigidbodyType2D::Dynamic };
};
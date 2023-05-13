/// Copyright (c) Vito Domenico Tagliente
#pragma once

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
	virtual void init() override;
	virtual void update(double /*deltaTime*/) override;

	const math::vec3& direction() const { return m_direction; }

	void move(const math::vec2& amount);
	void move(const math::vec3& amount);

	GENERATED_BODY()

private:
	class Collider2DComponent* m_collider{ nullptr };
	math::vec3 m_direction;
	math::vec3 m_lastPosition;
};
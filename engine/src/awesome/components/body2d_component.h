/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/scene/component.h>

#include "body2d_component_generated.h"

CLASS(Type = Component)
class Body2dComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double /*deltaTime*/) override;

	const math::vec3& direction()const { return m_direction; }

	void move(const math::vec2& amount);
	void move(const math::vec3& amount);

	GENERATED_BODY()

private:
	class Collider2dComponent* m_collider{ nullptr };
	math::vec3 m_direction;
	math::vec3 m_lastPosition;
};
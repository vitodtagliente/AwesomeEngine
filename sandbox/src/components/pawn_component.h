/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/math/vector3.h>
#include <awesome/scene/component.h>

#include "pawn_component_generated.h"

CLASS(Type = Component)
class PawnComponent : public Component
{
public:
	virtual void init() override;

	inline const math::vec3& getDirection() const { return m_direction; }

	void move(const math::vec3& direction, double deltaTime);
	void dash(double deltaTime);

	PROPERTY() float speed{ 3.0f };
	PROPERTY() float dashSpeed{ 12.0f };

	GENERATED_BODY()

private:
	class SpriteAnimatorComponent* m_animator{ nullptr };
	class Rigidbody2DComponent* m_body{ nullptr };
	math::vec3 m_direction{ math::vec3::right };
	class HealthComponent* m_health;
	class SpriteRendererComponent* m_renderer{ nullptr };
};
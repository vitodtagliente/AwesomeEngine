/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/body2d_component.h>
#include <awesome/component/sprite_animator_component.h>
#include <awesome/component/sprite_renderer_component.h>
#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

#include "pawn_component_generated.h"

CLASS(Category = Component)
class PawnComponent : public Component
{
public:
	PawnComponent() = default;
	virtual ~PawnComponent() = default;

	virtual void init() override;

	inline const math::vec3& getDirection() const { return m_direction; }

	void move(const math::vec3& direction, double deltaTime);
	void dash(double deltaTime);

	PROPERTY() float speed{ 3.0f };
	PROPERTY() float dashSpeed{ 12.0f };

	GENERATED_BODY()

private:
	SpriteAnimatorComponent* m_animator{ nullptr };
	Body2dComponent* m_body{ nullptr };
	math::vec3 m_direction{ math::vec3::right };
	class HealthComponent* m_health;
	SpriteRendererComponent* m_renderer{ nullptr };
};
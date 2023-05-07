/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/math/vector2.h>
#include <awesome/scene/component.h>

#include "collider2d_component_generated.h"

namespace graphics
{
	class Renderer;
}

ENUM()
enum class Collision2DShapeType : int
{
	Circle = 0,
	Rect
};

CLASS(Type = Component)
class Collider2dComponent : public Component
{
public:
	Collider2dComponent() = default;
	virtual ~Collider2dComponent() = default;

	void render(graphics::Renderer& renderer) override;

	bool collide(const Collider2dComponent& other);

	PROPERTY() bool isTrigger{ false };

	GENERATED_BODY()

private:
	PROPERTY() Collision2DShapeType m_type{ Collision2DShapeType::Rect };
	PROPERTY() math::vec2 m_bounds{ 1.0f, 1.0f };
	bool m_isColliding{ false };
};
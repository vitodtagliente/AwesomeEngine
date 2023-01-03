/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

#include <awesome/core/event.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/math/vector2.h>

#include "shape_type.h"

#include "collider2d_component_generated.h"

CLASS(Type = Component)
class Collider2dComponent : public graphics::IGraphicsComponent, public Component
{
public:
	Collider2dComponent() = default;
	virtual ~Collider2dComponent() = default;

	void render(class graphics::Renderer2D* const renderer) override;

	bool collide(const Collider2dComponent& other);

	virtual void inspect() override;

	PROPERTY() bool isTrigger{ false };
	event_t<const Collider2dComponent&> onCollision;
	event_t<const Collider2dComponent&> onTrigger;

	GENERATED_BODY()

private:
	PROPERTY() ShapeType m_type{ ShapeType::Rect };
	PROPERTY() math::vec2 m_bounds{ 1.0f, 1.0f };
	bool m_isColliding{ false };
};
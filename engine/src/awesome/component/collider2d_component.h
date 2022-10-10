/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/math/vector2.h>

#include "shape_type.h"

#include "collider2d_component_generated.h"

CLASS(Category = Component)
class Collider2dComponent : public graphics::IGraphicsComponent, public Component
{
public:
	Collider2dComponent() = default;
	virtual ~Collider2dComponent() = default;

	void render(class graphics::Renderer2D* const renderer) override;

	bool collide(const Collider2dComponent& other) const;

	virtual void inspect() override;

	std::function<void(const Collider2dComponent&)> onTrigger;
	PROPERTY() bool isTrigger{ false };

	GENERATED_BODY()

private:
	PROPERTY(IsEnum) ShapeType m_type{ ShapeType::Rect };
	PROPERTY() math::vec2 m_rectSize{ 1.0f, 1.0f };
	PROPERTY() float m_circleSize{ 1.0f };
};
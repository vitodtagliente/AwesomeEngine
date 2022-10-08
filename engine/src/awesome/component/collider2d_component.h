/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/math/vector2.h>

#include "shape_type.h"

#include "collider2d_component_generated.h"

namespace graphics
{
	class Renderer2D;
}

CLASS(Category = Component)
class Collider2dComponent : public graphics::IGraphicsComponent, public Component
{
public:
	typedef ShapeType Type;

	Collider2dComponent() = default;
	virtual ~Collider2dComponent() = default;

	void render(graphics::Renderer2D* const renderer) override;

	bool collide(const Collider2dComponent& other) const;

	std::function<void(const Collider2dComponent&)> onTrigger;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	PROPERTY() bool isTrigger{ false };

	GENERATED_BODY()

private:
	PROPERTY(IsEnum) Type m_type{ Type::Rect };
	PROPERTY() math::vec2 m_rectSize{ 1.0f, 1.0f };
	PROPERTY() float m_circleSize{ 1.0f };
};
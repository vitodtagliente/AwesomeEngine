/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/component.h>

#include "gizmos_renderer_component_generated.h"

CLASS(Category = Component)
class GizmosRendererComponent : public graphics::IGraphicsComponent, public Component
{
public:
	GizmosRendererComponent() = default;

	enum class Type : int
	{
		None,
		Rect,
		Circle
	};

	PROPERTY() Type type{ Type::None };
	PROPERTY() graphics::Color color{ graphics::Color::White };

	void render(class graphics::Renderer2D* const renderer) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	GENERATED_BODY()
};
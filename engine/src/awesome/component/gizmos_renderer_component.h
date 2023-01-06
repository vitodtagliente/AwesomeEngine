/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>
#include <awesome/entity/component.h>

#include "gizmos_renderer_component_generated.h"
#include "shape_type.h"

namespace graphics
{
	class Renderer2D;
}

CLASS(Type = Component)
class GizmosRendererComponent : public Component
{
public:
	GizmosRendererComponent() = default;

	PROPERTY(IsEnum) ShapeType type{ ShapeType::None };
	PROPERTY() graphics::Color color{ graphics::Color::White };

	void render(class graphics::Renderer2D* const renderer) override;

	GENERATED_BODY()
};
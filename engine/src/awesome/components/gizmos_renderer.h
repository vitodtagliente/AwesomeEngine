/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>

namespace graphics
{
	class Renderer;
}

class GizmosRenderer : public Component
{
public:
	GizmosRenderer();

	enum class Type
	{
		None,
		Rect,
		Circle
	};

	Type type;
	graphics::Color color;

	void render(graphics::Renderer& renderer) override;
	void inspect() override;
};
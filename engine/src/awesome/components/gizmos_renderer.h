/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/component.h>

namespace editor
{
	class Context;
}

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

	void render(graphics::Renderer* const renderer) override;
	void inspect(editor::Context& context) override;
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>

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
	Color color;

	void render(class Renderer& renderer) override;
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/graphics/color.h>

#include "editor_style_generated.h"

CLASS()
struct EditorStyle : public IType
{
	PROPERTY() graphics::Color activeColor{ 0.20f, 0.25f, 0.29f, 1.00f };
	PROPERTY() graphics::Color hoveredColor{ 0.26f, 0.59f, 0.98f, 0.80f };

	GENERATED_BODY()
};
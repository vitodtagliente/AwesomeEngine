/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>

class ColorScheme
{
public:
	ColorScheme() = default;

	void apply();

	graphics::Color activeColor{ 0.20f, 0.25f, 0.29f, 1.00f };
	graphics::Color hoveredColor{ 0.26f, 0.59f, 0.98f, 0.80f };
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtgraphics/color.h>

#include <awesome/core/reflection.h>

#include "color_generated.h"

NATIVE_CLASS(graphics::Color)
class Color
{
	PROPERTY() float red{ 0.0f };
	PROPERTY() float green{ 0.0f };
	PROPERTY() float blue{ 0.0f };
	PROPERTY() float alpha{ 1.0f };
};
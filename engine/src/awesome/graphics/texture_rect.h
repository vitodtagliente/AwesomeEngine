/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtgraphics/texture_rect.h>

#include <awesome/core/reflection.h>

#include "texture_rect_generated.h"

NATIVE_CLASS(graphics::TextureRect)
class TextureRect
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
	PROPERTY() float width{ 1.0f };
	PROPERTY() float height{ 1.0f };
};
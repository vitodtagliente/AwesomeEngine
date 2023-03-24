/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtgraphics/texture_coords.h>

#include <awesome/core/reflection.h>

#include "texture_coords_generated.h"

NATIVE_CLASS(graphics::TextureCoords)
class TextureCoords
{
	PROPERTY() float u{ 0.0f };
	PROPERTY() float v{ 0.0f };
};
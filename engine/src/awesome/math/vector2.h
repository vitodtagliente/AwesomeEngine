/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtmath/vector2.h>
#include <awesome/core/reflection.h>

#include "vector2_generated.h"

NATIVE_CLASS(math::vec2, namespace math { typedef struct vector2_t<float> vec2; })
struct Vec2
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
};
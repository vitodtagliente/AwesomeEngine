/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtmath/vector2.h>
#include <awesome/core/reflection.h>

#include "vector2_generated.h"

namespace math
{
	typedef vector2_t<int> vec2i;
}

NATIVE_CLASS(math::vec2, namespace math { typedef struct vector2_t<float> vec2; })
struct Vec2
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
};

NATIVE_CLASS(math::vec2i, namespace math { typedef struct vector2_t<int> vec2i; })
struct Vec2i
{
	PROPERTY() int x{ 0 };
	PROPERTY() int y{ 0 };
};
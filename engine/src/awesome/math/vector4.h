/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtmath/vector4.h>
#include <awesome/core/reflection.h>

#include "vector4_generated.h"

namespace math
{
	typedef vector4_t<int> vec4i;
}

NATIVE_CLASS(math::vec4, namespace math { typedef struct vector4_t<float> vec4; })
struct Vec4
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
	PROPERTY() float z{ 0.0f };
	PROPERTY() float w{ 0.0f };
};

NATIVE_CLASS(math::vec4i, namespace math { typedef struct vector4_t<int> vec4i; })
struct Vec4i
{
	PROPERTY() int x{ 0 };
	PROPERTY() int y{ 0 };
	PROPERTY() int z{ 0 };
	PROPERTY() int w{ 0 };
};
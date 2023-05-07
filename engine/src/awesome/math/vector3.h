/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtmath/vector3.h>
#include <awesome/core/reflection.h>

#include "vector3_generated.h"

namespace math
{
	typedef vector3_t<int> vec3i;
}

NATIVE_CLASS(math::vec3, namespace math { typedef struct vector3_t<float> vec3; })
struct Vec3
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
	PROPERTY() float z{ 0.0f };
};

NATIVE_CLASS(math::vec3i, namespace math { typedef struct vector3_t<int> vec3i; })
struct Vec3i
{
	PROPERTY() int x{ 0 };
	PROPERTY() int y{ 0 };
	PROPERTY() int z{ 0 };
};
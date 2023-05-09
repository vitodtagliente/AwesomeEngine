/// Copyright (c) Vito Domenico Tagliente
#pragma once
#pragma warning(disable : 4201)

#include <vdtmath/circle.h>
#include <awesome/core/reflection.h>

#include "circle_generated.h"

namespace math
{
	typedef circle_t<int> circlei;
}

NATIVE_CLASS(math::circle, namespace math { typedef struct circle_t<float> circle; })
struct Circle
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
	PROPERTY() float radius{ 0.0f };
};

NATIVE_CLASS(math::circlei, namespace math { typedef struct circle_t<int> circlei; })
struct Circlei
{
	PROPERTY() int x{ 0 };
	PROPERTY() int y{ 0 };
	PROPERTY() int radius{ 0 };
};
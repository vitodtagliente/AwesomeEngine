/// Copyright (c) Vito Domenico Tagliente
#pragma once
#pragma warning(disable : 4201)

#include <awesome/core/reflection.h>

#include "rectangle_t.h"
#include "rectangle_generated.h"

NATIVE_CLASS(math::rect, namespace math { typedef struct rectangle_t<float> rect; })
struct Rect
{
	PROPERTY() float x{ 0.0f };
	PROPERTY() float y{ 0.0f };
	PROPERTY() float width{ 0.0f };
	PROPERTY() float height{ 0.0f };
};

NATIVE_CLASS(math::recti, namespace math { typedef struct rectangle_t<int> recti; })
struct Recti
{
	PROPERTY() int x{ 0 };
	PROPERTY() int y{ 0 };
	PROPERTY() int width{ 0 };
	PROPERTY() int height{ 0 };
};
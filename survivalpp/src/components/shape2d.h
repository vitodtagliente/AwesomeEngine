#pragma once

#include "math/vector2.h"

enum class ShapeType2D
{
	Circle,
	Rect
};

struct Shape2D
{
	math::vec2 bounds{ 1.0f, 1.0f };
	ShapeType2D type{ ShapeType2D::Circle };
};
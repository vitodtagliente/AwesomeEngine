/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "ecs/component.h"

#include "math/vector2.h"

#include "shape2d.h"

enum class RigidbodyType2D : int
{
	Kinematic,
	Static
};

struct Rigidbody2D : public Component
{
	bool freezeRotation{ false };
	float gravityScale{ 9.8f };
	float mass{ 1.f };
	Shape2D shape;
	RigidbodyType2D type{ RigidbodyType2D::Kinematic };
	math::vec2 velocity{ math::vec2::zero };
};
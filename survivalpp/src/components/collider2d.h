/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "ecs/component.h"

#include "core/event.h"
#include "rigidbody2d.h"
#include "shape2d.h"

struct Collider2D : public Component
{
	Shape2D shape;

	event_t<const Rigidbody2D&> on_collision;
};
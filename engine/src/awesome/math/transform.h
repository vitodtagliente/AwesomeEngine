/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtmath/transform.h>
#include <awesome/core/reflection.h>

#include "transform_generated.h"

NATIVE_CLASS(math::transform)
class Transform
{
	PROPERTY() math::vec3 position;
	PROPERTY() math::vec3 rotation;
	PROPERTY() math::vec3 scale;
	PROPERTY() bool isStatic{ false };
};
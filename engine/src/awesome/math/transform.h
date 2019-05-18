#pragma once

#include "matrix.h"
#include "quaternion.h"
#include "transformation.h"
#include "vector.h"

namespace awesome
{
	struct transform
	{
		vector3 position;
		quaternion rotation;
		vector3 scale;
	};
}
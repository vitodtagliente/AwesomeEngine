#pragma once

#include "vector2.h"

namespace math
{
	struct transform2
	{
		vec2 position{ 0.f, 0.f };
		float rotation{ 0.f };
		vec2 scale{ 1.f, 1.f };
	};
}
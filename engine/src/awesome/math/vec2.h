#pragma once

namespace awesome
{
	struct vec2
	{
		float x, y;

		vec2 operator- (const vec2& other)
		{
			return { x - other.x, y - other.y };
		}
	};
}
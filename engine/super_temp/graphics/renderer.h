#pragma once

#include "../core/types.h"
#include "../data/color.h"

namespace awesome
{
	class Renderer
	{
	public:

		virtual void clear(const Color& t_color) = 0;
		virtual void draw(const uint t_vertices = 3) = 0;
		virtual void drawIndexed(const uint t_vertices) = 0;
	};
}
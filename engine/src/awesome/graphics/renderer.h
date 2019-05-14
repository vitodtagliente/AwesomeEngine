#pragma once

#include "../data/color.h"

namespace awesome
{
	class Renderer
	{
	public:

		virtual void clear(const Color& t_color) = 0;
		virtual void draw(const unsigned int t_vertices = 3) = 0;
		virtual void drawIndexed(const unsigned int t_vertices) = 0;
	};
}
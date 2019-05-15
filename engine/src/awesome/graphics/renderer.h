#pragma once

#include "../core/singleton.h"
#include "../data/color.h"

namespace awesome
{
	class Renderer : public Singleton<Renderer>
	{
	public:

		virtual void enableAlpha(const bool bEnabled = true) = 0;
		virtual void clear(const Color& t_color) = 0;
		virtual void draw(const unsigned int t_vertices = 3) = 0;
		virtual void drawIndexed(const unsigned int t_vertices) = 0;
	};
}
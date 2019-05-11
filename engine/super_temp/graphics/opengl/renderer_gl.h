#pragma once

#include "../renderer.h"

namespace awesome
{
	class RendererGL final : public Renderer
	{
	public:

		virtual void clear(const Color& t_color) override;
		virtual void draw(const uint t_vertices = 3) override;
		virtual void drawIndexed(const uint t_vertices) override;
	};
}
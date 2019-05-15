#pragma once

#include "../renderer.h"

namespace awesome
{
	class RendererGL final : public Renderer
	{
	public:

		virtual void enableAlpha(const bool bEnabled = true) override;
		virtual void clear(const Color& t_color) override;
		virtual void draw(const unsigned int t_vertices = 3) override;
		virtual void drawIndexed(const unsigned int t_vertices) override;
	};
}
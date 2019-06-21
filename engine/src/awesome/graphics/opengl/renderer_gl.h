#pragma once

#include "../renderer.h"

namespace awesome
{
	class GraphicsModule;

	class RendererGL final : public Renderer
	{
	public:

		RendererGL(GraphicsAPI* const t_api);

		virtual void enableAlpha(const bool bEnabled = true) override;
		virtual void clear(const Color& t_color) override;
		virtual void draw(const unsigned int t_vertices = 3) override;
		virtual void drawIndexed(const unsigned int t_vertices) override;
		virtual void setViewport(const int t_width, const int t_height) override;
	};
}
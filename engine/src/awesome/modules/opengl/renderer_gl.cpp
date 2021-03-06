#include "renderer_gl.h"

#include "opengl.h"
#include "graphics_api_gl.h"

namespace awesome
{
	RendererGL::RendererGL(GraphicsAPI* const t_api)
		: Renderer(t_api)
	{
	}

	void RendererGL::enableAlpha(const bool bEnabled)
	{
		if (bEnabled)
		{
			// Enable blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}

	void RendererGL::clear(const Color& t_color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(t_color.red, t_color.green, t_color.blue, t_color.alpha);
	}

	void RendererGL::draw(const unsigned int t_vertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, t_vertices);
	}

	void RendererGL::drawIndexed(const unsigned int t_vertices)
	{
		glDrawElements(GL_TRIANGLES, t_vertices, GL_UNSIGNED_INT, nullptr);
	}
	
	void RendererGL::setViewport(const int t_width, const int t_height)
	{
		glViewport(0, 0, t_width, t_height);
	}

	void RendererGL::setDrawingMode(const DrawingMode t_drawingMode)
	{
		switch (t_drawingMode)
		{
		case Renderer::DrawingMode::Lines:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case Renderer::DrawingMode::Fill:
		default:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		}
	}
}
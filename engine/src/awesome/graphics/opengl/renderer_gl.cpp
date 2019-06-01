#include "renderer_gl.h"

#include "opengl.h"
#include "graphics_module_gl.h"

namespace awesome
{
	RendererGL::RendererGL(GraphicsModule* const t_graphicsModule)
		: Renderer(t_graphicsModule)
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
}
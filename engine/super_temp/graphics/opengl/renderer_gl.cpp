#include "renderer_gl.h"

#include "opengl.h"

namespace awesome
{
	void RendererGL::clear(const Color& t_color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(t_color.red, t_color.green, t_color.blue, t_color.alpha);
	}

	void RendererGL::draw(const uint t_vertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, t_vertices);
	}

	void RendererGL::drawIndexed(const uint t_vertices)
	{
		glDrawElements(GL_TRIANGLES, t_vertices, GL_UNSIGNED_INT, nullptr);
	}
}
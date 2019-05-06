#include "graphics_gl.h"

#include "opengl.h"

namespace awesome
{
	bool GraphicsGL::startup_implementation()
	{
		return gladLoadGL();
	}

	void GraphicsGL::update_implementation()
	{
		// #todo
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.2f, .1f, .3f, 1.0f);
	}
}
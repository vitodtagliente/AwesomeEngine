#include "graphics_gl.h"

#include "opengl.h"

namespace awesome
{
	bool GraphicsGL::startup_implementation()
	{
		if (gladLoadGL())
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			return true;
		}
		return false;
	}

	void GraphicsGL::update_implementation()
	{
		// #todo
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.2f, .1f, .3f, 1.0f);
	}
}
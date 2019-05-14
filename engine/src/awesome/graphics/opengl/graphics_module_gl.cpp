#include "graphics_module_gl.h"

#include "opengl.h"
#include "renderer_gl.h"

namespace awesome
{
	GraphicsModuleGL::GraphicsModuleGL()
		: GraphicsModule(API::OpenGL)
	{
	}
	
	bool GraphicsModuleGL::startup_implementation()
	{
		if (gladLoadGL())
		{
			m_renderer = new RendererGL();
			return true;
		}
		return false;
	}
}
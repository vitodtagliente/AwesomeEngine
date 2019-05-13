#include "graphics_module_gl.h"

#include <glad/glad.h>

namespace awesome
{
	GraphicsModuleGL::GraphicsModuleGL()
		: GraphicsModule(API::OpenGL)
	{
	}
	
	bool GraphicsModuleGL::startup_implementation()
	{
		return gladLoadGL();
	}
}
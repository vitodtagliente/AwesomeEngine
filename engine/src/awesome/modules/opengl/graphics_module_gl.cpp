#include "graphics_module_gl.h"

#include "graphics_api_gl.h"
#include "renderer_gl.h"

namespace awesome
{
	GraphicsModuleGL::GraphicsModuleGL()
		: GraphicsModule()
	{
	}

	GraphicsAPI* const GraphicsModuleGL::createAPI() const
	{
		return new GraphicsAPI_GL();
	}

	Renderer* const GraphicsModuleGL::createRenderer(GraphicsAPI* const t_api) const
	{
		return new RendererGL(t_api);
	}


}
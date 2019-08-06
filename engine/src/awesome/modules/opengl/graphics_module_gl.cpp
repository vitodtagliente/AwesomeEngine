#include "graphics_module_gl.h"

#include "graphics_api_gl.h"
#include "renderer_gl.h"
#include "shaders.h"

#include <awesome/graphics/material.h>
#include <awesome/graphics/material_library.h>

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
		Renderer * const renderer = new RendererGL(t_api);

		// initialize default materials
		for (const std::pair<std::string, std::string>& shader : assets::shaders)
		{
			std::map<Shader::Type, std::string> sources;
			Shader::Reader::parse(shader.second, sources);
			// create shaders
			auto vertex = t_api->createShader(Shader::Type::Vertex, sources[Shader::Type::Vertex]);
			auto fragment = t_api->createShader(Shader::Type::Fragment, sources[Shader::Type::Fragment]);
			auto program = t_api->createShaderProgram({ vertex, fragment });

			// free shaders
			delete vertex;
			delete fragment;

			Material* const material = new Material(program);
			renderer->getMaterialLibrary()->add(shader.first, material);

		}
		
		return renderer;
	}

}
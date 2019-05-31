#include "graphics_module_gl.h"

#include "opengl.h"
#include "renderer_gl.h"

#include "graphics_buffer_gl.h"
#include "renderable_gl.h"
#include "shader_gl.h"
#include "shader_program_gl.h"
#include "texture_gl.h"

namespace awesome
{
	GraphicsModuleGL::GraphicsModuleGL()
		: GraphicsModule(API::OpenGL)
	{
	}

	Shader* GraphicsModuleGL::createShader(const Shader::Type t_type, const std::string& t_source) const
	{
		return new ShaderGL(t_type, t_source);
	}

	ShaderProgram* GraphicsModuleGL::createShaderProgram(const std::initializer_list<Shader*>& t_shaders) const
	{
		return new ShaderProgramGL(t_shaders);
	}

	Texture* GraphicsModuleGL::createTexture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height, const unsigned int t_components, const Texture::Options& t_options) const
	{
		return new TextureGL(t_data, t_width, t_height, t_components, t_options);
	}

	GraphicsBuffer* GraphicsModuleGL::createBuffer(const GraphicsBuffer::Type t_type, const void* const t_data, const std::size_t t_size)
	{
		return new GraphicsBufferGL(t_type, t_data, t_size);
	}

	Renderable* GraphicsModuleGL::createRenderable(const Mesh& t_mesh)
	{
		return new RenderableGL(t_mesh);
	}
		
	bool GraphicsModuleGL::startup_implementation()
	{
		if (gladLoadGL())
		{
			m_renderer = new RendererGL();
			// #todo: to be removed
			glViewport(0, 0, 640, 480);
			return true;
		}
		return false;
	}
}
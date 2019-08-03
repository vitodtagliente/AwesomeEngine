#include "graphics_api_gl.h"

#include "opengl.h"

#include "renderable_gl.h"
#include "shader_gl.h"
#include "shader_program_gl.h"
#include "texture_gl.h"

namespace awesome
{
	GraphicsAPI_GL::GraphicsAPI_GL()
		: GraphicsAPI(GraphicsAPI::Type::OpenGL)
	{
	}

	GraphicsAPI_GL::~GraphicsAPI_GL()
	{
	}

	bool GraphicsAPI_GL::startup()
	{
		return gladLoadGL();
	}
	
	void GraphicsAPI_GL::shutdown()
	{
	}
	
	void GraphicsAPI_GL::clear(const Color& t_color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(t_color.red, t_color.green, t_color.blue, t_color.alpha);
	}
	
	void GraphicsAPI_GL::setViewport(const unsigned int t_width, const unsigned int t_height)
	{
		glViewport(0, 0, t_width, t_height);
	}
	
	void GraphicsAPI_GL::draw(const unsigned int t_vertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, t_vertices);
	}
	
	void GraphicsAPI_GL::drawIndexed(const unsigned int t_indices)
	{
		glDrawElements(GL_TRIANGLES, t_indices, GL_UNSIGNED_INT, nullptr);
	}
	
	void GraphicsAPI_GL::enableAlpha(const bool t_enabled)
	{
		if (t_enabled)
		{
			// Enable blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
	
	Shader* GraphicsAPI_GL::createShader(const Shader::Type t_type, const std::string& t_source) const
	{
		return new ShaderGL(t_type, t_source);
	}
	
	ShaderProgram* GraphicsAPI_GL::createShaderProgram(const std::initializer_list<Shader*>& t_shaders) const
	{
		return new ShaderProgramGL(t_shaders);
	}
	
	Texture* GraphicsAPI_GL::createTexture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height, const unsigned int t_components, const Texture::Options& t_options) const
	{
		return new TextureGL(t_data, t_width, t_height, t_components, t_options);
	}
	
	Renderable* GraphicsAPI_GL::createRenderable(const Mesh& t_mesh)
	{
		return new RenderableGL(t_mesh);
	}
}
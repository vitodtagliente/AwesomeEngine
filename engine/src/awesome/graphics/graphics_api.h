#pragma once 

#include <initializer_list>
#include <string>

#include <awesome/data/color.h>
#include "mesh/mesh.h"
#include "renderable.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"

namespace awesome
{
	class GraphicsAPI
	{
	public:

		enum class Type
		{
			Null,
			OpenGL
		};

		GraphicsAPI() = default;
		~GraphicsAPI() = default;

		virtual bool startup() = 0;
		virtual void shutdown() = 0;

		// low level api abstraction
		virtual void clear(const Color& t_color) = 0;
		virtual void setViewport(const unsigned int t_width, const unsigned int t_height) = 0;
		virtual void draw(const unsigned int t_vertices = 3) = 0;
		virtual void drawIndexed(const unsigned int t_indices) = 0;

		virtual void enableAlpha(const bool t_enabled = true) = 0;

		// graphics objects creation
		virtual Shader* createShader(const Shader::Type t_type, const std::string& t_source) const = 0;
		virtual ShaderProgram* createShaderProgram(const std::initializer_list<Shader*>& t_shaders) const = 0;
		virtual Texture* createTexture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
			const unsigned int t_components, const Texture::Options& t_options = Texture::Options{}) const = 0;
		virtual Renderable* createRenderable(const Mesh& t_mesh) = 0;
	};
}
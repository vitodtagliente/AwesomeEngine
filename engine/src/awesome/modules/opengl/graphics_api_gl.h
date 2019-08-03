#pragma once

#include <awesome/graphics/graphics_api.h>

namespace awesome
{
	class GraphicsAPI_GL : public GraphicsAPI
	{
	public:

		GraphicsAPI_GL();
		~GraphicsAPI_GL();

		virtual bool startup() override;
		virtual void shutdown() override;

		// low level api abstraction
		virtual void clear(const Color& t_color) override;
		virtual void setViewport(const unsigned int t_width, const unsigned int t_height) override;
		virtual void draw(const unsigned int t_vertices = 3) override;
		virtual void drawIndexed(const unsigned int t_indices) override;

		virtual void enableAlpha(const bool t_enabled = true) override;

		// graphics objects creation
		virtual Shader* createShader(const Shader::Type t_type, const std::string& t_source) const override;
		virtual ShaderProgram* createShaderProgram(const std::initializer_list<Shader*>& t_shaders) const override;
		virtual Texture* createTexture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
			const unsigned int t_components, const Texture::Options& t_options = Texture::Options{}) const override;
		virtual Renderable* createRenderable(const Mesh& t_mesh) override;
	};
}
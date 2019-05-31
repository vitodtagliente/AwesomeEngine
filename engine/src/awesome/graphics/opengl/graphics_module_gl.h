#pragma once

#include "../graphics_module.h"

namespace awesome
{
	class GraphicsModuleGL final : public GraphicsModule
	{
	public:

		GraphicsModuleGL();

		virtual Shader* createShader(const Shader::Type t_type, const std::string& t_source) const override;
		virtual ShaderProgram* createShaderProgram(const std::initializer_list<Shader*>& t_shaders) const override;
		virtual Texture* createTexture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
			const unsigned int t_components, const Texture::Options& t_options = Texture::Options{}) const override;
		virtual GraphicsBuffer* createBuffer(const GraphicsBuffer::Type t_type, const void* const t_data,
			const std::size_t t_size) override;
		virtual Renderable* createRenderable(const Mesh& t_mesh) override;

	protected:

		virtual bool startup_implementation() override;

	};
}
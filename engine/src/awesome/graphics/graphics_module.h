#pragma once

#include <initializer_list>
#include <string>
#include "../core/singleton.h"
#include "../engine/module.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"

namespace awesome
{
	class Renderer;

	class GraphicsModule : public Module, public Singleton<GraphicsModule>
	{
	public:

		enum class API
		{
			Null,
			OpenGL
		};

		GraphicsModule(const API t_api);
		~GraphicsModule();

		inline API getAPI() const { return m_api; }
		inline Renderer* getRenderer() const { return m_renderer; }

		virtual Shader* createShader(const Shader::Type t_type, const std::string& t_source) const = 0;
		virtual ShaderProgram* createShaderProgram(const std::initializer_list<Shader*>& t_shaders) const = 0;
		virtual Texture* createTexture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
			const unsigned int t_components, const Texture::Options& t_options = Texture::Options{}) const = 0;

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		// used api
		API m_api;
		// renderer
		Renderer* m_renderer;
	};
}
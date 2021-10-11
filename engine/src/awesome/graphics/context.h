/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <awesome/core/singleton.h>
#include <vdtmath/matrix4.h>
#include <vdtmath/vector3.h>

#include "color.h"
#include "renderable.h"
#include "shader_program.h"
#include "shader_library.h"
#include "texture_rect.h"

namespace graphics
{
	class Texture;

	class Context : public Singleton<Context>
	{
	public:
		Context();

		void clear(const Color& color);
		void viewport(int width, int height);
		void drawLines(const std::vector<std::pair<math::vec3, Color>>& points);
		void drawSprites(Texture* const texture, const std::vector<std::pair<math::mat4, TextureRect>>& sprites);

		void test();

		math::mat4 camera;
		Texture* testTexture;

	private:

		ShaderProgram* const createProgram(const std::string& name);

		ShaderLibrary m_shaderLibrary;
		Renderable m_gizmosRenderingData;
		Renderable m_spritebatchRenderingData;
		ShaderProgram* m_gizmosProgram;
		ShaderProgram* m_colorProgram;
		ShaderProgram* m_spritebatchProgram;
		ShaderProgram* m_textureProgram;
	};
}
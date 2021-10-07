/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/transform.h>
#include <vdtmath/vector3.h>
#include "color.h"
#include "renderable.h"
#include "shader_program.h"
#include "shader_library.h"
#include "texture.h"
#include "texture_rect.h"

class Context
{
public:
	Context();

	void clear(const Color& color);
	void viewport(int width, int height);
	void drawLines(const std::vector<std::pair<math::vec3, Color>>& points);
	void drawSprites(Texture* const texture, const std::vector<std::pair<math::transform, TextureRect>>& sprites);

	void test();

	math::mat4 camera;

private:

	ShaderProgram* const createProgram(const std::string& name);

	ShaderLibrary m_shaderLibrary;
	Renderable m_gizmosRenderingData;
	Renderable m_spritebatchRenderingData;
	ShaderProgram* m_gizmosProgram;
	ShaderProgram* m_colorProgram;
	ShaderProgram* m_spritebatchProgram;
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/matrix4.h>
#include <vdtmath/vector3.h>
#include "color.h"
#include "renderable.h"
#include "shader_program.h"
#include "shader_library.h"

class Context
{
public:
	Context();

	void clear(const Color& color);
	void viewport(int width, int height);
	void drawLines(const std::vector<std::pair<math::vec3, Color>>& points);

	void test();

	math::mat4 camera;

private:

	ShaderProgram* const createProgram(const std::string& name);

	ShaderLibrary m_shaderLibrary;
	Renderable m_gizmosRenderingData;
	ShaderProgram* m_gizmosProgram;
	ShaderProgram* m_colorProgram;
};
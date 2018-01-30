#pragma once

#include <vector>

namespace Instinct
{
	namespace Rendering
	{
		struct Mesh
		{
			unsigned int vao;
			unsigned int vbo;

			std::vector<float> vertices;
			std::vector<float> uv;
		};
	}
}
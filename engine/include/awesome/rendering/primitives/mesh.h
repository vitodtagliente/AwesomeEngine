#pragma once

#include <vector>
#include "../../math/math.h"

namespace Awesome
{
	namespace Rendering
	{
		struct Mesh
		{
			unsigned int vao{ 0 };
			unsigned int vbo{ 0 };
			unsigned int ebo{ 0 };
			unsigned int eab{ 0 }; 

			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> normals;
			
			std::vector<int> indices;

			virtual void init();

			void bind();
			void unbind();
		};
	}
}
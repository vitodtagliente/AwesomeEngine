#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Awesome
{
	namespace Rendering
	{
		struct Mesh
		{
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> normals;
			
			std::vector<int> indices;

			virtual void init();
		};
	}
}
#include <awesome/rendering/primitives/triangle.h>

namespace Awesome
{
	namespace Rendering
	{
		Triangle::Triangle()
		{
			vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

			uvs.push_back(glm::vec2(0.5f, 1.0f));
			uvs.push_back(glm::vec2(0.0f, 0.0f));
			uvs.push_back(glm::vec2(1.0f, 0.0f));
		}
	}
}
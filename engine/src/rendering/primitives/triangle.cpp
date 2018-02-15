#include <awesome/rendering/primitives/triangle.h>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
	{
		Triangle::Triangle()
		{
			vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
}
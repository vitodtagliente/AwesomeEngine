#include <dreamkeeper/primitives/triangle.h>

namespace Dreamkeeper
{
	namespace Primitives
	{
		Triangle::Triangle() {
			/* fill vertices */
			vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
}
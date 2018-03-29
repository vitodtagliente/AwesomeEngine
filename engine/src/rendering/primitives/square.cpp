#include <awesome/rendering/primitives/square.h>

namespace Awesome
{
	Square::Square()
	{
		/* top right */
		vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		/* bottom right */
		vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
		/* bottom left */
		vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
		/* top left */
		vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

		uvs.push_back(glm::vec2(0.0f, 1.0f));
		uvs.push_back(glm::vec2(0.0f, 0.0f));
		uvs.push_back(glm::vec2(1.0f, 0.0f));
		uvs.push_back(glm::vec2(1.0f, 1.0f));

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(3); 
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
	}
}
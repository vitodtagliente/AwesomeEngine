#include <awesome/rendering/primitives/cube.h>

namespace Awesome
{
	Cube::Cube()
	{
		/* front */
		vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
		vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
		vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		/* back */
		vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
		vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
		vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

		/* front */
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(0);
		/* top */
		indices.push_back(1);
		indices.push_back(5);
		indices.push_back(6);
		indices.push_back(6);
		indices.push_back(2);
		indices.push_back(1);
		/* back */
		indices.push_back(7);
		indices.push_back(6);
		indices.push_back(5);
		indices.push_back(5);
		indices.push_back(4);
		indices.push_back(7);
		/* bottom */
		indices.push_back(4);
		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(3);
		indices.push_back(7);
		indices.push_back(4);
		/* left */
		indices.push_back(4);
		indices.push_back(5);
		indices.push_back(1);
		indices.push_back(1);
		indices.push_back(0);
		indices.push_back(4);
		/* right */
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(6);
		indices.push_back(6);
		indices.push_back(7);
		indices.push_back(3);
	}
}
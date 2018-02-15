#include <awesome/rendering/primitives/square.h>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
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

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(3); 
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(3);
		}
	}
}
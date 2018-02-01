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

		void Square::init()
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				3 * sizeof(float),  // stride
				(void*)0            // array buffer offset
			);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Square::draw()
		{
			/* bind the mesh vertices */
			bind();
			/* draw the mesh */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}
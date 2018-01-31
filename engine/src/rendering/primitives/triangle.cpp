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

		void Triangle::init()
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Triangle::draw()
		{
			/* bind the mesh vertices */
			bind();
			/* draw the mesh */
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}
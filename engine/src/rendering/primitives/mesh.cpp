#include <awesome/rendering/primitives/mesh.h>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
	{
		void Mesh::init() 
		{
			std::vector<float> data{};
			for (int i = 0; i < vertices.size(); i++)
			{
				data.push_back(vertices[i].x);
				data.push_back(vertices[i].y);
				data.push_back(vertices[i].z);
			}
			for (int i = 0; i < uvs.size(); i++)
			{
				data.push_back(uvs[i].x);
				data.push_back(uvs[i].y);
			}

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
			
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,					// stride
				(void*)0		    // array buffer offset
			);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(
				1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				2,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,					// stride
				(void*)(vertices.size() * sizeof(glm::vec3))		    // array buffer offset
			);
			glEnableVertexAttribArray(1);

			/* create an element array buffer */
			if (indices.size() > 0)
			{
				glGenBuffers(1, &eab);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
			}
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		
		void Mesh::bind() 
		{
			glBindVertexArray(vao);
		}

		void Mesh::unbind()
		{
			glBindVertexArray(0);
		}
	}
}
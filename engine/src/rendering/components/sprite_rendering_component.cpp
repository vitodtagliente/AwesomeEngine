#include <awesome/rendering/components/sprite_rendering_component.h>
#include <awesome/rendering/shading/texture.h>
#include <awesome/rendering/primitives/primitives.h>
#include <glad/glad.h>
#include <vector>

namespace Awesome
{
	namespace Rendering
	{
		void SpriteRenderingComponent::init()
		{
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<int> indices;

			vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

			uvs.push_back(glm::vec2(textureCoords.x, textureCoords.height));
			uvs.push_back(glm::vec2(textureCoords.x, textureCoords.y));
			uvs.push_back(glm::vec2(textureCoords.width, textureCoords.y));
			uvs.push_back(glm::vec2(textureCoords.width, textureCoords.height));

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(3);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(3);

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,					// stride
				(void*)0		    // array buffer offset
			);
			glEnableVertexAttribArray(0);

			glGenBuffers(1, &uv_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
			glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_DYNAMIC_DRAW);

			glVertexAttribPointer(
				1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				2,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,					// stride
				(void*)0		    // array buffer offset
			);
			glEnableVertexAttribArray(1);

			/* create an element array buffer */
			glGenBuffers(1, &eab);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void SpriteRenderingComponent::crop(const Math::Rect& crop)
		{
			if (textureCoords != crop)
			{
				textureCoords = crop;

				if (vao != 0)
				{
					std::vector<glm::vec2> uvs;
					uvs.push_back(glm::vec2(crop.x, crop.height));
					uvs.push_back(glm::vec2(crop.x, crop.y));
					uvs.push_back(glm::vec2(crop.width, crop.y));
					uvs.push_back(glm::vec2(crop.width, crop.height));

					glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
					glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(glm::vec2), &uvs[0]);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}
			}
		}

		void SpriteRenderingComponent::update(float delta_time)
		{

		}

		void SpriteRenderingComponent::render()
		{
			texture->bind();
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			RenderingComponent::render();
			glBindVertexArray(0);
		}
	}
}
#include <awesome/rendering/sprite_batch.h>
#include <awesome/rendering/objects/camera.h>
#include <awesome/rendering/context.h>

namespace Awesome
{
	namespace Rendering
	{
		SpriteBatch* SpriteBatch::singleton = nullptr;

		SpriteBatch::SpriteBatch() {

		}

		SpriteBatch::~SpriteBatch() {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &uv_vbo);
			glDeleteBuffers(1, &eab);
		}

		SpriteBatch* SpriteBatch::instance() 
		{
			if (singleton == nullptr)
			{
				singleton = new SpriteBatch();
				singleton->init();
			}
			return singleton;
		}

		void SpriteBatch::init() 
		{
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<int> indices;

			vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
			vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
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
			
			/* clear rendering data */
			data.clear();
		}

		void SpriteBatch::clear() {
			data.clear();
		}

		void SpriteBatch::add(Texture* texture, const SpriteBatchRenderingData& in_data) 
		{
			if (data.find(texture) == data.end())
			{
				std::vector<SpriteBatchRenderingData> v;
				data.insert(std::make_pair(texture, v));
			}
			data[texture].push_back(in_data);
		}

		void SpriteBatch::draw() 
		{
			for (auto it = data.begin(); it != data.end(); ++it) 
			{
				auto texture = it->first;
				if (texture != nullptr)
				{
					texture->bind();
					glBindVertexArray(vao);

					auto camera = Camera::main();
					SpriteBatchRenderingData last_rendering_data;
					bool first = true;

					for (auto rendering_data : it->second)
					{
						if (rendering_data.material != nullptr && rendering_data.material->program != nullptr)
						{
							auto program = rendering_data.material->program;
							if (camera != nullptr)
							{
								if (first || (last_rendering_data.material != nullptr &&
									last_rendering_data.material->program != program))
								{
									program->use();
									/* setup camera matrices */
									program->setMat4("projection", camera->getProjection());
									program->setMat4("view", camera->getView());
								}
								/* setup model matrix */
								program->setMat4("model", rendering_data.transform);
							}
						}

						if (first || last_rendering_data.textureCoords != rendering_data.textureCoords)
						{
							std::vector<glm::vec2> uvs;
							auto crop = rendering_data.textureCoords;
							uvs.push_back(glm::vec2(crop.x, crop.y + crop.height));
							uvs.push_back(glm::vec2(crop.x, crop.y));
							uvs.push_back(glm::vec2(crop.x + crop.width, crop.y));
							uvs.push_back(glm::vec2(crop.x + crop.width, crop.y + crop.height));

							glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
							glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(glm::vec2), &uvs[0]);
							glBindBuffer(GL_ARRAY_BUFFER, 0);
						}						

						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

						last_rendering_data = rendering_data;
						first = false;
					}
					glBindVertexArray(0);
				}
			}
			/* clear rendering data at the end of drawing phase */
			clear();
		}
	}
}
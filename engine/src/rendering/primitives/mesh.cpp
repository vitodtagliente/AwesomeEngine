#include <dreamkeeper/primitives/mesh.h>

namespace Dreamkeeper
{
	namespace Primitives
	{
		Mesh::Mesh() {

		}
		
		Mesh::Mesh(std::vector<glm::vec3> vertices)
		{
			this->vertices = vertices;
		}


		void Mesh::finalize()
		{
			std::vector<float> data{};
			for (int i = 0; i < vertices.size(); i++) {
				data.push_back(vertices[i].x);
				data.push_back(vertices[i].y);
				data.push_back(vertices[i].z);
			}

			vao.bind();
			vbo.bind();
			vbo.allocate(data.size() * sizeof(float), &data[0]);
			VertexArrayAttribute position;
			position.count = 3;
			position.format(0, 0);
			position.enable();
			vao.unbind();
		}
		
		void Mesh::bind()
		{
			vao.bind();
		}

		void Mesh::unbind()
		{
			vao.unbind();
		}
	}
}
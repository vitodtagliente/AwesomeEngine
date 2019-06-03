#include "mesh.h"

namespace awesome
{
	Mesh::Mesh()
		: vertices()
		, indices()
	{
	
	}

	Mesh::Mesh(const std::vector<VertexData>& t_vertices)
		: vertices(t_vertices)
		, indices()
	{
	}

	Mesh::Mesh(const std::vector<VertexData>& t_vertices, const std::vector<unsigned int>& t_indices)
		: vertices(t_vertices)
		, indices(t_indices)
	{
	}

	Mesh::Mesh(const Mesh& t_mesh)
	{
		vertices = t_mesh.vertices;
		indices = t_mesh.indices;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::getData(std::vector<float>& t_data) const
	{
		t_data.clear();

		for (const VertexData& vertex_data : vertices)
		{
			// vertex position
			t_data.push_back(vertex_data.position.x);
			t_data.push_back(vertex_data.position.y);
			t_data.push_back(vertex_data.position.z);
			// vertex uv
			t_data.push_back(vertex_data.uv.x);
			t_data.push_back(vertex_data.uv.y);
		}
	}

	Mesh& Mesh::operator=(const Mesh& t_mesh)
	{
		vertices = t_mesh.vertices;
		indices = t_mesh.indices;
		return *this;
	}

}
#include "mesh.h"

namespace awesome
{
	Mesh::Mesh()
		: topology(Topology::Triangles)
		, positions()
		, uvs()
		, normals()
		, indices()
	{
	
	}

	Mesh::Mesh(const Topology t_topology)
		: topology(t_topology)
		, positions()
		, uvs()
		, normals()
		, indices()
	{
	}

	Mesh::Mesh(const Topology t_topology, 
		const std::vector<vector3>& t_positions, 
		const std::vector<unsigned int>& t_indices)
		: topology(t_topology)
		, positions(t_positions)
		, uvs()
		, normals()
		, indices(t_indices)
	{
	}

	Mesh::Mesh(const Topology t_topology, 
		const std::vector<vector3>& t_positions,
		const std::vector<vector2>& t_uvs, 
		const std::vector<unsigned int>& t_indices)
		: topology(t_topology)
		, positions(t_positions)
		, uvs(t_uvs)
		, normals()
		, indices(t_indices)
	{
	}

	Mesh::Mesh(const Mesh& t_mesh)
	{
		positions = t_mesh.positions;
		uvs = t_mesh.uvs;
		normals = t_mesh.normals;
		indices = t_mesh.indices;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::getData(std::vector<float>& t_data) const
	{
		t_data.clear();

		for (int i = 0; i < positions.size(); ++i)
		{
			const vector3& position = positions[i];
			t_data.push_back(position.x);
			t_data.push_back(position.y);
			t_data.push_back(position.z);

			if (uvs.size() > 0)
			{
				const vector2& uv = uvs[i];
				t_data.push_back(uv.x);
				t_data.push_back(uv.y);
			}
		}
	}

	Mesh& Mesh::operator=(const Mesh& t_mesh)
	{
		positions = t_mesh.positions;
		uvs = t_mesh.uvs;
		normals = t_mesh.normals;
		indices = t_mesh.indices;
		return *this;
	}

}
#include "mesh.h"

namespace awesome
{
	Mesh::Mesh()
		: topology(Topology::Triangles)
		, positions()
		, uv()
		, normals()
		, indices()
	{
	
	}

	Mesh::Mesh(const Topology t_topology)
		: topology(t_topology)
		, positions()
		, uv()
		, normals()
		, indices()
	{
	}

	Mesh::Mesh(const Topology t_topology, 
		const std::vector<vector3>& t_positions, 
		const std::vector<unsigned int>& t_indices)
		: topology(t_topology)
		, positions(t_positions)
		, uv()
		, normals()
		, indices(t_indices)
	{
	}

	Mesh::Mesh(const Topology t_topology, 
		const std::vector<vector3>& t_positions,
		const std::vector<vector2>& t_uv, 
		const std::vector<unsigned int>& t_indices)
		: topology(t_topology)
		, positions(t_positions)
		, uv(t_uv)
		, normals()
		, indices(t_indices)
	{
	}

	Mesh::~Mesh()
	{
	}

	Mesh * const Mesh::create(const Primitive t_primitive)
	{
		return nullptr;
	}
}
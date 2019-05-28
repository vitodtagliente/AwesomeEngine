#include "mesh.h"

namespace awesome
{
	Mesh::Mesh()
		: m_topology(Topology::Triangles)
		, m_positions()
		, m_uv()
		, m_normals()
		, m_indices()
	{
	
	}

	Mesh::Mesh(const Topology t_topology)
		: m_topology(t_topology)
		, m_positions()
		, m_uv()
		, m_normals()
		, m_indices()
	{
	}

	Mesh::Mesh(const Topology t_topology, 
		const std::vector<vector3>& t_positions, 
		const std::vector<unsigned int>& t_indices)
		: m_topology(t_topology)
		, m_positions(t_positions)
		, m_uv()
		, m_normals()
		, m_indices(t_indices)
	{
	}

	Mesh::Mesh(const Topology t_topology, 
		const std::vector<vector3>& t_positions,
		const std::vector<vector2>& t_uv, 
		const std::vector<unsigned int>& t_indices)
		: m_topology(t_topology)
		, m_positions(t_positions)
		, m_uv(t_uv)
		, m_normals()
		, m_indices(t_indices)
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::setPositions(const std::vector<vector3>& t_positions)
	{
		m_positions = t_positions;
	}

	void Mesh::setUV(const std::vector<vector2>& t_uv)
	{
		m_uv = t_uv;
	}

	void Mesh::setNormals(const std::vector<vector3>& t_normals)
	{
		m_normals = t_normals;
	}

	void Mesh::setIndices(const std::vector<unsigned int>& t_indices)
	{
		m_indices = t_indices;
	}

	Mesh * const Mesh::create(const Primitive t_primitive)
	{
		return nullptr;
	}
}
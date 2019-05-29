#pragma once

#include <vector>
#include "../../math/vector.h"

namespace awesome
{
	struct Mesh
	{
	public:

		enum class Topology
		{
			Points,
			Lines,
			LineStrip,
			Triangles,
			TriangleStrip
		};

		enum class Primitive
		{
			Triangle,
			Quad,
			Cube
		};

		Mesh();
		Mesh(const Topology t_topology);
		Mesh(const Topology t_topology, 
			const std::vector<vector3>& t_positions, 
			const std::vector<unsigned int>& t_indices);
		Mesh(const Topology t_topology,
			const std::vector<vector3>& t_positions,
			const std::vector<vector2>& t_uv, 
			const std::vector<unsigned int>& t_indices);
		Mesh(const Mesh& t_mesh);
		virtual ~Mesh();

		Mesh& operator= (const Mesh& t_mesh);

		// mesh topology
		Topology topology;

		// vertex data
		std::vector<vector3> positions;
		std::vector<vector2> uv;
		std::vector<vector3> normals;
		// index data
		std::vector<unsigned int> indices;
	};
}
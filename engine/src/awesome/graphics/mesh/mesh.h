#pragma once

#include <vector>
#include "../../math/vector.h"

namespace awesome
{
	class Mesh
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
		virtual ~Mesh();

		inline Topology getTopology() const { return m_topology; }
		inline const std::vector<vector3>& getPositions() const { return m_positions; }
		inline const std::vector<vector2>& getUV() const { return m_uv; }
		inline const std::vector<vector3>& getNormals() const { return m_normals; }
		inline const std::vector<unsigned int>& getIndices() const { return m_indices; }

		void setPositions(const std::vector<vector3>& t_positions);
		void setUV(const std::vector<vector2>& t_uv);
		void setNormals(const std::vector<vector3>& t_normals);
		void setIndices(const std::vector<unsigned int>& t_indices);

		static Mesh * const create(const Primitive t_primitive);

	protected:

		Topology m_topology;

		// vertex data
		std::vector<vector3> m_positions;
		std::vector<vector2> m_uv;
		std::vector<vector3> m_normals;
		// index data
		std::vector<unsigned int> m_indices;
	};
}
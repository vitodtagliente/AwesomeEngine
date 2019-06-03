#pragma once

#include <vector>
#include "../../math/vector.h"

namespace awesome
{
	struct Mesh
	{
	public:

		struct VertexData
		{
			vector3 position;
			vector2 uv;

		};

		Mesh();
		Mesh(const std::vector<VertexData>& t_vertices);
		Mesh(const std::vector<VertexData>& t_vertices, const std::vector<unsigned int>& t_indices);
		Mesh(const Mesh& t_mesh);
		virtual ~Mesh();

		void getData(std::vector<float>& t_data) const;

		Mesh& operator= (const Mesh& t_mesh);
		
		// vertex data
		std::vector<VertexData> vertices;
		// index data
		std::vector<unsigned int> indices;
	};
}
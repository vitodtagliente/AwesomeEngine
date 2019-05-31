#include "quad.h"

namespace awesome
{
	Quad::Quad(const Mesh::Topology t_topology)
		: Mesh(t_topology)
	{
		positions.push_back({ -1.0f, -1.0f, 0.0f });
		positions.push_back({ 1.0f,	-1.0f, 0.0f });
		positions.push_back({ 1.0f,	1.0f, 0.0f });
		positions.push_back({ -1.0f, 1.0f, 0.0f });

		uvs.push_back({ 0.0f, 0.0f });
		uvs.push_back({ 1.0f, 0.0f });
		uvs.push_back({ 1.0f, 1.0f });
		uvs.push_back({ 0.0f, 1.0f });

		indices = { 0, 1, 2, 2, 3, 0 };
	}
}
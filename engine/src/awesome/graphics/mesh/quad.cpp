#include "quad.h"

namespace awesome
{
	Quad::Quad(const Mesh::Topology t_topology)
		: Mesh(t_topology)
	{
		// top right
		positions.push_back({ 1.0f, 1.0f, 0.0f });
		// bottom right
		positions.push_back({ 1.0f,	-1.0f, 0.0f });
		// bottom left
		positions.push_back({ -1.0f, -1.0f, 0.0f });
		// top left
		positions.push_back({ -1.0f, 1.0f, 0.0f });

		uvs.push_back({ 1.0f, 1.0f });
		uvs.push_back({ 1.0f, 0.0f });
		uvs.push_back({ 0.0f, 0.0f });
		uvs.push_back({ 0.0f, 1.0f });

		indices = { 0, 1, 3, 1, 2, 3 };
	}
}
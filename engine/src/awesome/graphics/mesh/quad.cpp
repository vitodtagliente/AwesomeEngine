#include "quad.h"

namespace awesome
{
	Quad::Quad()
		: Mesh()
	{
		// top right
		vertices.push_back({ { 1.0f, 1.0f, 0.0f }, {1.0, 1.0f} });
		// bottom right
		vertices.push_back({ { 1.0f, -1.0f, 0.0f }, {1.0, 0.0f} });
		// bottom left
		vertices.push_back({ { -1.0f, -1.0f, 0.0f }, {0.0, 0.0f} });
		// top left
		vertices.push_back({ { -1.0f, 1.0f, 0.0f }, {0.0, 1.0f} });

		indices = { 0, 1, 3, 1, 2, 3 };
	}
}
#include "circle.h"

namespace awesome
{
	Circle::Circle(const unsigned int t_steps)
		: Mesh()
	{
		float theta = 0.0f;
		const float step_amount = 360.0f / t_steps;
		// center vertex
		vertices.push_back({});
		vertices.push_back({ {cosf(theta), sinf(theta), 0.0f}, {0.0f, 0.0f} });
		for (unsigned int i = 0; i < t_steps; ++i)
		{
			vertices.push_back({ {cosf(theta), sinf(theta), 0.0f}, {0.0f, 0.0f} });
			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(i + 2);
			theta += step_amount;
		}
	}
}
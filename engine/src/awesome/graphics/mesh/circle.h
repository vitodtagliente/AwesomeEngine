#pragma once

#include "mesh.h"

namespace awesome
{
	struct Circle : public Mesh
	{
	public:

		Circle(const unsigned int t_steps = 360);

	};
}
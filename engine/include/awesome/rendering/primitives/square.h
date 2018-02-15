#pragma once

#include "mesh.h"

namespace Awesome
{
	namespace Rendering
	{
		struct Square : public Mesh
		{
			Square();

			void init() override;
		};
	}
}
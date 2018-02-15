#pragma once 

#include "mesh.h"

namespace Awesome
{
	namespace Rendering
	{
		struct Triangle : public Mesh
		{
			Triangle();

			void init() override;
		};
	}
}
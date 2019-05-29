#pragma once

#include "../math/matrix4.h"

namespace awesome
{
	// All render state required for submitting a render command.
	
	class Material;
	class Mesh;

	struct RenderCommand
	{
		Material* material;
		Mesh* mesh;
		matrix4 transform;
	};
}
#pragma once

namespace awesome
{
	// All render state required for submitting a render command.
	
	class Material;
	class Mesh;

	struct RenderCommand
	{
		Material* material;
		Mesh* mesh;
	};
}
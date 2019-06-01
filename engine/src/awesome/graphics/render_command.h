#pragma once

#include "../math/matrix4.h"

namespace awesome
{
	// All render state required for submitting a render command.
	
	class Material;
	class Renderable;

	struct RenderCommand
	{
		Renderable* renderable;
		Material* material;
		matrix4 transform;

		RenderCommand()
			: renderable()
			, material()
			, transform(matrix4::identity)
		{

		}

		RenderCommand(
			Renderable* const t_renderable,
			Material* const t_material,
			const matrix4& t_transform = matrix4::identity
		)
			: renderable(t_renderable)
			, material(t_material)
			, transform(t_transform)
		{

		}
	};
}
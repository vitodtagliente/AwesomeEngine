#pragma once

#include <awesome/engine/component.h>
#include <awesome/graphics/material.h>

namespace awesome
{
	class Renderer;

	class RenderingComponent : public Component
	{
	public:

		virtual void push_data(Renderer* const t_renderer) = 0;

		// material
		Material* material;
	};
}
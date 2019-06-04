#pragma once

#include "../../scene/component.h"
#include "../material.h"

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
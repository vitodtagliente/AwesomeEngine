#pragma once

#include "rendering_component.h"

namespace awesome
{
	class MeshComponent : public RenderingComponent
	{
	public:

		virtual void push_data(Renderer* const t_renderer) override;
	};
}
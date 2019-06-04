#pragma once

#include "rendering_component.h"

namespace awesome
{
	class SpriteComponent : public RenderingComponent
	{
	public:

		virtual void push_data(Renderer* const t_renderer) override;
	};
}
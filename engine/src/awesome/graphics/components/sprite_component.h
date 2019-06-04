#pragma once

#include "rendering_component.h"

namespace awesome
{
	class Texture;

	class SpriteComponent : public RenderingComponent
	{
	public:

		virtual void push_data(Renderer* const t_renderer) override;

		// sprite texture
		Texture* texture;
	};
}
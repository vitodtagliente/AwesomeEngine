#pragma once

#include "rendering_component.h"

namespace Awesome
{
	namespace Rendering
	{
		class Texture;

		class SpriteRenderingComponent : public RenderingComponent
		{
		public:
			Texture* texture{ nullptr };

			void init() override;
			void update(float delta_time) override;
			void render() override;
		};
	}
}
#pragma once

#include "mesh_rendering_component.h"

namespace Awesome
{
	namespace Rendering
	{
		class Texture;

		class SpriteRenderingComponent : public MeshRenderingComponent
		{
		public:
			Texture* texture{ nullptr };
			bool cropTexture{ false };

			void init() override;
			void update(float delta_time) override;
			void render() override;
		};
	}
}
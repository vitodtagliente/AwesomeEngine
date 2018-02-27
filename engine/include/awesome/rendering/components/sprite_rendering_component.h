#pragma once

#include "mesh_rendering_component.h"
#include "../../math/rect.h"

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

			Math::Rect cropRect{ 0.0f,0.0f, 1.0f,1.0f };

			void init() override;
			void update(float delta_time) override;
			void render() override;
		};
	}
}
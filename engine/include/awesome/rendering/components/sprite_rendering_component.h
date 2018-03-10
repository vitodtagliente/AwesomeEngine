#pragma once

#include "rendering_component.h"
#include "../../math/rect.h"

namespace Awesome
{
	namespace Rendering
	{
		class Texture;

		class SpriteRenderingComponent : public RenderingComponent
		{
		protected:
			/* used to crop texture atlas */
			Math::Rect textureCoords{ 0.0f,0.0f, 1.0f,1.0f };

		public:
			Texture* texture{ nullptr };

			void crop(const Math::Rect& crop);

			void init() override;
			void update(float delta_time) override;
			void render() override;
		};
	}
}
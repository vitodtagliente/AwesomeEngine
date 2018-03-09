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
		private:
			unsigned int vao{ 0 };
			unsigned int vbo{ 0 };
			unsigned int uv_vbo{ 0 };
			unsigned int ebo{ 0 };
			unsigned int eab{ 0 };

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
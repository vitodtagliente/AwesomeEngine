#pragma once

#include "rendering_component.h"
#include "../shading/texture.h"
#include "../../math/rect.h"

namespace Awesome
{
	class SpriteRenderingComponent : public RenderingComponent
	{
	protected:
		// used to crop texture atlas 
		Rect textureCoords{ 0.0f,0.0f, 1.0f,1.0f };

	public:
		Texture* texture{ nullptr };

		void crop(const Rect& crop);

		void init() override;
		void update(float delta_time) override;
		void render() override;
	};
}
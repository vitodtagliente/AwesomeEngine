#pragma once 

#include "../../scenegraph/object.h"
#include "../components/sprite_rendering_component.h"

namespace Awesome
{
	namespace Rendering
	{
		class Sprite : public Scenegraph::Object
		{
		private:
			SpriteRenderingComponent* spriteRenderingComponent{ nullptr };

		public:
			Sprite(std::string name);
			SpriteRenderingComponent* spriteRenderer() { return spriteRenderingComponent; }
		};
	}
}
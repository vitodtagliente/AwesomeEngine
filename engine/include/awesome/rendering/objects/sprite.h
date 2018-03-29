#pragma once 

#include "../../object.h"
#include "../components/sprite_rendering_component.h"

namespace Awesome
{
	class Sprite : public Object
	{
	private:
		SpriteRenderingComponent* spriteRenderingComponent{ nullptr };

	public:
		Sprite(std::string name);
		SpriteRenderingComponent* spriteRenderer() { return spriteRenderingComponent; }
	};
}
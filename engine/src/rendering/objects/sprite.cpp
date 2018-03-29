#include <awesome/rendering/objects/sprite.h>

namespace Awesome
{
	Sprite::Sprite(std::string name)
	{
		spriteRenderingComponent = addComponent<SpriteRenderingComponent>();
	}
}
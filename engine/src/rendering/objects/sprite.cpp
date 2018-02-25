#include <awesome/rendering/objects/sprite.h>

namespace Awesome
{
	namespace Rendering
	{
		Sprite::Sprite(std::string name) : Object(name)
		{
			spriteRenderingComponent = addComponent<SpriteRenderingComponent>();
		}
	}
}
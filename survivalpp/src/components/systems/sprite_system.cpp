#include "sprite_system.h"

#include "graphics/common.h"
#include "graphics/renderer.h"
#include "graphics/texture_library.h"

void SpriteSystem::process(const double, Sprite& sprite)
{
	graphics::Texture* const texture = graphics::TextureLibrary::instance().find(sprite.texture);
	if (texture)
	{
		math::transform2 transform = sprite.entity()->transform;
		graphics::Renderer::instance().sprites->draw(texture, math::vec3(transform.position.x, transform.position.y, 0.f), sprite.rect);
	}
}

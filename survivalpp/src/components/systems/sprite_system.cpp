#include "sprite_system.h"

#include "graphics/common.h"
#include "graphics/renderer.h"
#include "graphics/texture_library.h"

extern graphics::Renderer* g_renderer;

void SpriteSystem::process(const double, Sprite& sprite)
{
	graphics::TextureFlipMode flip = graphics::TextureFlipMode::None;
	if (sprite.flipX) flip = graphics::TextureFlipMode::Horizontal;
	if (sprite.flipY)
	{
		if (flip == graphics::TextureFlipMode::Horizontal)
			flip = graphics::TextureFlipMode::Both;
		else flip = graphics::TextureFlipMode::Vertical;
	}

	graphics::Texture* const texture = graphics::TextureLibrary::instance().find(sprite.texture);
	if (texture)
	{
		math::transform2 transform = sprite.entity()->transform;
		g_renderer->submitDrawTexture(*texture, transform.position, transform.rotation, transform.scale, sprite.rect, flip);
	}
}

#include "sprite_renderer.h"

#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, image()
	, rect()
{

}

void SpriteRenderer::render(graphics::Renderer* const renderer)
{
	if (image != nullptr)
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance()->find(image->id);
		if (texture)
		{
			renderer->drawSprite(texture.get(), getOwner()->transform.matrix(), rect);
		}
	}
}

#include "sprite_renderer.h"

#include <awesome/scene/entity.h>
#include <awesome/graphics/renderer.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, texture()
	, rect()
{

}

void SpriteRenderer::render(Renderer& renderer)
{
	if (texture != nullptr)
	{
		renderer.drawSprite(texture, getOwner()->transform.matrix(), rect);
	}
}
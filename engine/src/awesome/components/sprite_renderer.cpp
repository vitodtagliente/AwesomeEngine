#include "sprite_renderer.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, sprite()
	, color(graphics::Color::White)
{

}

void SpriteRenderer::render(graphics::Renderer* const renderer)
{
	if (sprite && sprite->data.image)
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance()->find(sprite->data.image->id);
		if (texture)
		{
			renderer->drawSprite(texture.get(), getOwner()->transform.matrix(), sprite->data.rect);
		}
	}
}

json::value SpriteRenderer::serialize() const
{
	json::value data = Component::serialize();
	data.insert("color", ::serialize(color));
	return data;
}

void SpriteRenderer::inspect()
{
	Component::inspect();
	editor::Layout::input("Sprite", sprite);
	editor::Layout::input("Color", color);
}

REFLECT_COMPONENT(SpriteRenderer)
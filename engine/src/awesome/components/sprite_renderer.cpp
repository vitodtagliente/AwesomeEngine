#include "sprite_renderer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_asset.h>
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
	if (sprite && sprite->data.has_value())
	{
		const Sprite& data = sprite->data.value();
		if (data.image)
		{
			std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(data.image->descriptor.id);
			if (texture)
			{
				renderer->drawSprite(texture.get(), getOwner()->transform.matrix(), data.rect);
			}

		}		
	}
}

json::value SpriteRenderer::serialize() const
{
	json::value data = Component::serialize();
	data["sprite"] = sprite ? ::serialize(sprite->descriptor.id) : "";
	data["color"] = ::serialize(color);
	return data;
}

void SpriteRenderer::deserialize(const json::value& value)
{
	Component::deserialize(value);

	uuid spriteId = uuid::Invalid;
	::deserialize(value["sprite"], spriteId);
	sprite = AssetLibrary::instance().find<SpriteAsset>(spriteId);
	::deserialize(value["color"], color);
}

void SpriteRenderer::inspect()
{
	Component::inspect();
	editor::Layout::input("Sprite", sprite);
	editor::Layout::input("Color", color);
}

REFLECT_COMPONENT(SpriteRenderer)
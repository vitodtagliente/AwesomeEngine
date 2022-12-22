#include "sprite_asset_inspector.h"

#include <awesome/asset/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

bool SpriteAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->descriptor.type == Asset::Type::Sprite;
}

void SpriteAssetInspector::inspect(const AssetPtr& asset)
{
	SpriteAssetPtr sprite = std::static_pointer_cast<SpriteAsset>(asset);

	auto& data = sprite->data.value();
	Layout::input("Image", data.image);
	Layout::input("Rect", data.rect);
	Layout::image(data.image, data.rect);

	if (Layout::collapsingHeader("Reference"))
	{
		Layout::image(data.image);
	}

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		data.save(sprite->descriptor.path.parent_path() / sprite->descriptor.path.stem());
	}
}
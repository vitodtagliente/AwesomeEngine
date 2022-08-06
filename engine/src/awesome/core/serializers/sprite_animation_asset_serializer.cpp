#include "sprite_animation_asset_serializer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_animation_asset.h>

std::string SpriteAnimationAssetSerializer::type()
{
	return "SpriteAnimationAssetPtr";
}

json::value SpriteAnimationAssetSerializer::serialize(const FieldDescriptor& field)
{
	const SpriteAnimationAssetPtr& asset = field.value<SpriteAnimationAssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool SpriteAnimationAssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	SpriteAnimationAssetPtr& asset = field.value<SpriteAnimationAssetPtr>();
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		asset = AssetLibrary::instance().find<SpriteAnimationAsset>(assetId);
	}
	return true;
}

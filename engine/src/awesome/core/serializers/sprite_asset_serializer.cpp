#include "sprite_asset_serializer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_asset.h>

std::string SpriteAssetSerializer::type()
{
	return "SpriteAssetPtr";
}

json::value SpriteAssetSerializer::serialize(const FieldDescriptor& field)
{
	const SpriteAssetPtr& asset = field.value<SpriteAssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool SpriteAssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	SpriteAssetPtr& asset = field.value<SpriteAssetPtr>();
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		asset = AssetLibrary::instance().find<SpriteAsset>(assetId);
	}
	return true;
}

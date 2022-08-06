#include "asset_serializer.h"

#include <awesome/asset/asset_library.h>

#include <awesome/asset/image_asset.h>
#include <awesome/asset/prefab_asset.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/asset/text_asset.h>

bool AssetSerializer::canSerialize(const FieldDescriptor& field)
{
	return field.typeStr == "ImageAssetPtr"
		|| field.typeStr == "PrefabAssetPtr"
		|| field.typeStr == "SceneAssetPtr"
		|| field.typeStr == "SpriteAnimationAssetPtr"
		|| field.typeStr == "SpriteAssetPtr"
		|| field.typeStr == "TextAssetPtr"
		;
}

json::value AssetSerializer::serialize(const FieldDescriptor& field)
{
	const AssetPtr& asset = field.value<AssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool AssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		if (field.typeStr == "ImageAssetPtr")
		{
			field.value<ImageAssetPtr>() = AssetLibrary::instance().find<ImageAsset>(assetId);
		}
		else if (field.typeStr == "PrefabAssetPtr")
		{
			field.value<PrefabAssetPtr>() = AssetLibrary::instance().find<PrefabAsset>(assetId);
		}
		else if (field.typeStr == "SceneAssetPtr")
		{
			field.value<SceneAssetPtr>() = AssetLibrary::instance().find<SceneAsset>(assetId);
		}
		else if (field.typeStr == "SpriteAnimationAssetPtr")
		{
			field.value<SpriteAnimationAssetPtr>() = AssetLibrary::instance().find<SpriteAnimationAsset>(assetId);
		}
		else if (field.typeStr == "SpriteAssetPtr")
		{
			field.value<SpriteAssetPtr>() = AssetLibrary::instance().find<SpriteAsset>(assetId);
		}
		else if (field.typeStr == "TextAssetPtr")
		{
			field.value<TextAssetPtr>() = AssetLibrary::instance().find<TextAsset>(assetId);
		}
	}
	return true;
}
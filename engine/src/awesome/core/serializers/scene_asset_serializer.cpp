#include "scene_asset_serializer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/scene_asset.h>

std::string SceneAssetSerializer::type()
{
	return "SceneAssetPtr";
}

json::value SceneAssetSerializer::serialize(const FieldDescriptor& field)
{
	const SceneAssetPtr& asset = field.value<SceneAssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool SceneAssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	SceneAssetPtr& asset = field.value<SceneAssetPtr>();
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		asset = AssetLibrary::instance().find<SceneAsset>(assetId);
	}
	return true;
}

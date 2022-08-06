#include "prefab_asset_serializer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/prefab_asset.h>

std::string PrefabAssetSerializer::type()
{
	return "PrefabAssetPtr";
}

json::value PrefabAssetSerializer::serialize(const FieldDescriptor& field)
{
	const PrefabAssetPtr& asset = field.value<PrefabAssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool PrefabAssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	PrefabAssetPtr& asset = field.value<PrefabAssetPtr>();
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		asset = AssetLibrary::instance().find<PrefabAsset>(assetId);
	}
	return true;
}

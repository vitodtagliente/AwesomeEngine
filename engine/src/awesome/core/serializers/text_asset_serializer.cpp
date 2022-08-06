#include "text_asset_serializer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/text_asset.h>

std::string TextAssetSerializer::type()
{
	return "TextAssetPtr";
}

json::value TextAssetSerializer::serialize(const FieldDescriptor& field)
{
	const TextAssetPtr& asset = field.value<TextAssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool TextAssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	TextAssetPtr& asset = field.value<TextAssetPtr>();
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		asset = AssetLibrary::instance().find<TextAsset>(assetId);
	}
	return true;
}

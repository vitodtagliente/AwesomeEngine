#include "image_asset_serializer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/image_asset.h>

std::string ImageAssetSerializer::type()
{
	return "ImageAssetPtr";
}

json::value ImageAssetSerializer::serialize(const FieldDescriptor& field)
{
	const ImageAssetPtr& asset = field.value<ImageAssetPtr>();
	return asset ? static_cast<std::string>(asset->descriptor.id) : "";
}

bool ImageAssetSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	ImageAssetPtr& asset = field.value<ImageAssetPtr>();
	const uuid assetId = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	if (assetId != uuid::Invalid)
	{
		asset = AssetLibrary::instance().find<ImageAsset>(assetId);
	}
	return true;
}

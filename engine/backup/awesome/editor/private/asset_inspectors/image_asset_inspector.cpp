#include "image_asset_inspector.h"

#include <awesome/asset/image_asset.h>
#include <awesome/editor/layout.h>

bool ImageAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->getTypeName() == ImageAsset::staticTypeName();
}

void ImageAssetInspector::inspect(const AssetPtr& asset)
{
	ImageAssetPtr image = std::static_pointer_cast<ImageAsset>(asset);
	Layout::image(image);
}
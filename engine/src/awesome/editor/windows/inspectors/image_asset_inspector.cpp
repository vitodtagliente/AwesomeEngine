#include "image_asset_inspector.h"

#include <awesome/asset/image_asset.h>
#include <awesome/editor/widgets/form_layout.h>

bool ImageAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->type == AssetType_Image;
}

void ImageAssetInspector::inspect(const AssetPtr& asset)
{
	std::shared_ptr<ImageAsset> image = std::static_pointer_cast<ImageAsset>(asset);
	FormLayout::image(image);
}
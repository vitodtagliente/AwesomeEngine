#include "image_asset_inspector.h"

#include <awesome/asset/image_asset.h>
#include <awesome/editor/widgets/form_layout.h>

bool ImageAssetInspector::canInspect(const AssetRecord* const record)
{
	return record->type == ImageAsset::Type;
}

void ImageAssetInspector::inspect(const AssetRecord* const record)
{
	if (m_imageAsset.id != record->id)
	{
		m_imageAsset = ImageAsset(record->id);
		m_imageAsset.load();
	}

	FormLayout::image(m_imageAsset);
}
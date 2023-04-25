#include "image_asset_inspector.h"

#include <awesome/asset/image_asset.h>
#include <awesome/editor/widgets/form_layout.h>

bool ImageAssetInspector::canInspect(const AssetRecord& record)
{
	return record.type == ImageAsset::Type;
}

void ImageAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = ImageAsset(record.id);
		m_asset.load();
	}

	FormLayout::image(m_asset);
}
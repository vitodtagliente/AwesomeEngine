#include "image_asset_inspector.h"

#include <awesome/editor/editor_ui.h>

bool ImageAssetInspector::canInspect(int type) const
{
	return type == ImageAsset::Type;
}

char* const ImageAssetInspector::getTitle() const
{
	return "Image";
}

void ImageAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = ImageAsset(record.id);
		m_asset.load();
	}

	EditorUI::image(m_asset);
}
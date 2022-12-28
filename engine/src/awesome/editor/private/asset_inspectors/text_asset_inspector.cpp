#include "text_asset_inspector.h"

#include <awesome/asset/text_asset.h>
#include <awesome/editor/layout.h>

bool TextAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->descriptor.type == Asset::Type::Text;
}

void TextAssetInspector::inspect(const AssetPtr& asset)
{
	TextAssetPtr text = std::static_pointer_cast<TextAsset>(asset);
	Layout::textWrapped(text->data.value());
}
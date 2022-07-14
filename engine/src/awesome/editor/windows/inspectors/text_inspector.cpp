#include "text_inspector.h"

#include <awesome/asset/text_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool TextInspector::canInspect(const AssetPtr& asset)
	{
		return asset->descriptor.type == Asset::Type::Text;
	}

	void TextInspector::inspect(const AssetPtr& asset)
	{
		TextAssetPtr text = std::static_pointer_cast<TextAsset>(asset);
		if (asset == nullptr)
		{
			return;
		}

		if (!text->data.has_value())
		{
			Layout::text("Loading...");
			return;
		}

		Layout::textWrapped(text->data.value());
	}
}
#include "text_inspector.h"

#include <awesome/asset/text_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool TextInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->descriptor.type == Asset::Type::Text;
	}

	void TextInspector::inspect(const State::Selection& selection)
	{
		TextAssetPtr asset = std::static_pointer_cast<TextAsset>(selection.asAsset());
		if (asset == nullptr || !asset->data.has_value())
		{
			return;
		}

		Layout::textWrapped(asset->data.value());
	}
}
#include "text_inspector.h"

#include <awesome/data/text_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

namespace editor
{
	bool TextInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Text;
	}

	void TextInspector::inspect(const State::Selection& selection, const std::filesystem::path&)
	{
		TextAssetPtr asset = std::static_pointer_cast<TextAsset>(selection.asAsset());
		if (asset == nullptr)
		{
			return;
		}

		Layout::textWrapped(asset->data);
	}
}
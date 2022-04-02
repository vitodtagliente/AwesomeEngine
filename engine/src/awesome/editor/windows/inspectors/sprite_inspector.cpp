#include "sprite_inspector.h"

#include <awesome/data/sprite_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool SpriteInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Sprite;
	}

	void SpriteInspector::inspect(const State::Selection& selection, const std::filesystem::path&)
	{
		SpriteAssetPtr sprite = std::static_pointer_cast<SpriteAsset>(selection.asAsset());
		if (sprite == nullptr)
		{
			return;
		}

		Layout::image(sprite->data.image, sprite->data.rect);
		Layout::input("Rect", sprite->data.rect);
	}
}
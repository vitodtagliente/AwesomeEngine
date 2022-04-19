#include "sprite_inspector.h"

#include <awesome/data/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	bool SpriteInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Sprite;
	}

	void SpriteInspector::inspect(const State::Selection& selection)
	{
		SpriteAssetPtr sprite = std::static_pointer_cast<SpriteAsset>(selection.asAsset());
		if (sprite == nullptr)
		{
			return;
		}

		Layout::input("Image", sprite->data.image);
		Layout::input("Rect", sprite->data.rect);
		Layout::image(sprite->data.image, sprite->data.rect);
		
		if (Layout::collapsingHeader("Reference"))
		{
			Layout::image(sprite->data.image);
		}

		Layout::separator();
		
		if (Layout::button(TextIcon::save(" Save")))
		{
			sprite->data.save(sprite->filename.parent_path() / sprite->filename.stem());
		}
	}
}
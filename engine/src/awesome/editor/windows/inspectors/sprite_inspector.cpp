#include "sprite_inspector.h"

#include <awesome/data/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	bool SpriteInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->descriptor.type == Asset::Type::Sprite;
	}

	void SpriteInspector::inspect(const State::Selection& selection)
	{
		SpriteAssetPtr sprite = std::static_pointer_cast<SpriteAsset>(selection.asAsset());
		if (sprite == nullptr || !sprite->data.has_value())
		{
			return;
		}

		auto& data = sprite->data.value();
		Layout::input("Image", data.image);
		Layout::input("Rect", data.rect);
		Layout::image(data.image, data.rect);
		
		if (Layout::collapsingHeader("Reference"))
		{
			Layout::image(data.image);
		}

		Layout::separator();
		
		if (Layout::button(TextIcon::save(" Save")))
		{
			data.save(sprite->descriptor.path.parent_path() / sprite->descriptor.path.stem());
		}
	}
}
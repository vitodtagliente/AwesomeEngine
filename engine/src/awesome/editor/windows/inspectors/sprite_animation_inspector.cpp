#include "sprite_animation_inspector.h"

#include <awesome/data/sprite_animation_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool SpriteAnimationInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::SpriteAnimation;
	}

	void SpriteAnimationInspector::inspect(const State::Selection& selection)
	{
		SpriteAnimationAssetPtr sprite = std::static_pointer_cast<SpriteAnimationAsset>(selection.asAsset());
		if (sprite == nullptr)
		{
			return;
		}

		// TODO
	}
}
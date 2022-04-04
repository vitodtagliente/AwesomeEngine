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

	void SpriteAnimationInspector::inspect(const State::Selection& selection, const std::filesystem::path&)
	{
		SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(selection.asAsset());
		if (animation == nullptr)
		{
			return;
		}

		Layout::input("Frames", animation->data.frames);

		Layout::separator();
		if (Layout::button("Save"))
		{
			animation->data.save(animation->filename.parent_path() / animation->filename.stem());
		}
	}
}
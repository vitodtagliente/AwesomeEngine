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

		// Layout::input("Starting Frame", (int)animation->data.startingFrame);
		for (size_t i = 0; i < animation->data.frames.size(); ++i)
		{
			auto& frames = animation->data.frames;
			SpriteAnimation::Frame& frame = frames.at(i);

			const std::string name = std::string("Frame ") + std::to_string(i);

			Layout::beginContext(name);
			if (Layout::collapsingHeader(name))
			{
				Layout::input("Sprite", frame.sprite);
				Layout::input("Duration", frame.duration);
				if (Layout::button("-"))
				{
					frames.erase(frames.begin() + i);
					return;
				}
			}
			Layout::endContext();
		}
		Layout::separator();
		{
			if (Layout::button("+"))
			{
				animation->data.frames.push_back(SpriteAnimation::Frame());
			}
			Layout::sameLine();
			if (Layout::button("X"))
			{
				animation->data.frames.clear();
			}
		}
	}
}
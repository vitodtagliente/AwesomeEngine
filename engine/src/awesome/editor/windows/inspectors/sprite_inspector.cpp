#include "sprite_inspector.h"

#include <awesome/data/asset_importer.h>
#include <awesome/data/sprite_animation.h>
#include <awesome/editor/layout.h>

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

		Layout::image(sprite->data.image, sprite->data.rect);
		Layout::input("Rect", sprite->data.rect);
		if (Layout::collapsingHeader("Reference"))
		{
			Layout::image(sprite->data.image);
		}
		Layout::separator();
		if (Layout::button("Save"))
		{
			sprite->data.save(sprite->filename.parent_path() / sprite->filename.stem());
		}

		// if (Layout::collapsingHeader("Animation"))
		// {
		// 	Layout::input("Filename", m_filename);
		// 	Layout::separator();
		// 	if (Layout::button("Save"))
		// 	{
		// 		const std::string name = m_filename.c_str();
		// 		if (!name.empty())
		// 		{
		// 			const std::string filename = (path / name).string() + ".spriteanim";
		// 			SpriteAnimation animation;
		// 			animation.save(filename);
		// 
		// 			AssetImporter importer;
		// 			importer.import(filename);
		// 		}
		// 		m_filename.clear();
		// 	}
		// }
	}
}
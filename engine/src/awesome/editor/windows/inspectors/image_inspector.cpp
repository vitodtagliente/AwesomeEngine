#include "image_inspector.h"

#include <awesome/data/image_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool ImageInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Image;
	}

	void ImageInspector::inspect(const State::Selection& selection)
	{
		ImageAssetPtr image = std::static_pointer_cast<ImageAsset>(selection.asAsset());
		if (image == nullptr)
		{
			return;
		}

		Layout::image(image);
		// if (Layout::collapsingHeader("Sprite Editor"))
		// {
		// 	Layout::input("Filename", &m_filename, 300);
		// 	Layout::input("Rect", m_rect);
		// 	if (Layout::button("Save Sprite"))
		// 	{
		// 		const std::string name = m_filename.c_str();
		// 		if (!name.empty())
		// 		{
		// 			const std::string filename = (getState()->workPath / name).string() + ".sprite";
		// 			Sprite sprite(image, m_rect);
		// 			sprite.save(filename);
		// 
		// 			AssetImporter importer;
		// 			importer.import(filename);
		// 		}
		// 		m_filename.clear();
		// 		m_rect = graphics::TextureRect();
		// 	}
		// }
		// if (Layout::collapsingHeader("Sprite Animation"))
		// {
		// 	Layout::input("Filename", &m_filename, 300);
		// 	if (Layout::button("Save Animation"))
		// 	{
		// 		const std::string name = m_filename.c_str();
		// 		if (!name.empty())
		// 		{
		// 			const std::string filename = (getState()->workPath / name).string() + ".spriteanim";
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
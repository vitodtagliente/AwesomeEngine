#include "image_inspector.h"

#include <awesome/data/image_asset.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/layout.h>

namespace editor
{
	ImageInspector::ImageInspector()
		: m_previousSelectedAsset()
		, m_filename()
		, m_rect()
	{

	}

	bool ImageInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Image;
	}

	void ImageInspector::inspect(const State::Selection& selection, const std::filesystem::path& path)
	{
		ImageAssetPtr image = std::static_pointer_cast<ImageAsset>(selection.asAsset());

		const bool hasChanged = m_previousSelectedAsset != image.get();
		m_previousSelectedAsset = image.get();

		if (image == nullptr)
		{
			return;
		}

		if (hasChanged)
		{
			m_filename.clear();
			m_rect = graphics::TextureRect();
		}

		Layout::image(image);
		if (Layout::collapsingHeader("Sprite Editor"))
		{
			Layout::input("Filename", m_filename);
			Layout::input("Rect", m_rect);
			Layout::image(image, m_rect);
			if (Layout::button("Save Sprite"))
			{
				const std::string name = m_filename.c_str();
				if (!name.empty())
				{
					const std::string filename = (path / name).string() + ".sprite";
					Sprite sprite(image, m_rect);
					sprite.save(filename);
		
					AssetImporter importer;
					importer.import(filename);
				}
				m_filename.clear();
				m_rect = graphics::TextureRect();
			}
		}
	}
}
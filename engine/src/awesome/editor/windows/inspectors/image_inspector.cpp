#include "image_inspector.h"

#include <awesome/data/asset_importer.h>
#include <awesome/data/image_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	ImageInspector::ImageInspector()
		: m_fileDialog(".sprite")
	{
	}

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

		Layout::separator();

		if (Layout::button("Generate Sprite"))
		{
			m_fileDialog.open([&image](const std::filesystem::path& filename) -> void
				{
					if (!filename.string().empty())
					{
						Sprite sprite(image, graphics::TextureRect());
						sprite.save(filename);
						
						AssetImporter importer;
						importer.import(filename);
					}
				}
			);
		}

		m_fileDialog.render("Save Sprite...");
	}
}
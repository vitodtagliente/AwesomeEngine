#include "image_inspector.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool ImageInspector::canInspect(const AssetPtr& asset)
	{
		return asset->descriptor.type == Asset::Type::Image;
	}

	void ImageInspector::inspect(const AssetPtr& asset)
	{
		ImageAssetPtr image = std::static_pointer_cast<ImageAsset>(asset);
		if (image == nullptr || !image->data.has_value())
		{
			return;
		}

		if (image != m_previouslySelectedImage)
		{
			m_previouslySelectedImage = image;
			m_rows = m_columns = 0;
			m_padding.x = m_padding.y = 0.0f;
		}

		Layout::image(image);

		if (Layout::collapsingHeader("SpriteSheet Editor"))
		{
			Layout::input("Rows", m_rows);
			Layout::input("Columns", m_columns);
			Layout::input("Padding", m_padding);

			Layout::image(image, graphics::TextureRect(
				m_padding.x,
				m_padding.y,
				m_columns > 0 ? 1.0f / m_columns : 1.0f,
				m_rows > 0 ? 1.0f / m_rows : 1.0f
			));

			Layout::separator();

			if (Layout::button(TextIcon::save(" Save")) && m_rows > 0 && m_columns > 0)
			{
				Dialog::instance().save("Save SpriteSheet...", Asset::getExtensionByType(Asset::Type::Sprite), [&image, rows = m_rows, columns = m_columns, padding = m_padding](const std::filesystem::path& path) -> void
					{
						if (!path.string().empty())
						{
							const float width = 1.0f / columns;
							const float height = 1.0f / rows;

							for (int i = 0; i < rows; ++i)
							{
								for (int j = 0; j < columns; ++j)
								{
									const std::filesystem::path file = path.parent_path() / (
										path.stem().string()
										+ "-" + std::to_string(i) + std::to_string(j)
										+ path.extension().string()
										);

									SpriteAsset::data_t sprite(image, graphics::TextureRect(width * j + padding.x, height * i + padding.y, width, height));
									sprite.save(file);

									AssetImporter importer;
									importer.import(file);
								}
							}
						}
					}
				);
			}
		}
	}
}
#include "sprite_menu_item.h"

#include <filesystem>

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/sprite_asset.h>

namespace editor
{
	void SpriteMenuItem::render()
	{
		m_saveFileDialog.render();
	}

	void SpriteMenuItem::execute()
	{
		m_saveFileDialog.open("Save Sprite...", Asset::getExtensionByType(Asset::Type::Sprite), [](const std::filesystem::path& filename) -> void
			{
				if (!filename.string().empty())
				{
					SpriteAsset::data_t sprite(nullptr, graphics::TextureRect());
					sprite.save(filename);

					AssetImporter importer;
					importer.import(filename);
				}
			}
		);
	}

	REFLECT_MENU_ITEM(SpriteMenuItem)
}
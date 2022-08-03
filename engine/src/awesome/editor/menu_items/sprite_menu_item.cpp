#include "sprite_menu_item.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/editor/dialog.h>

namespace editor
{
	void SpriteMenuItem::execute()
	{
		Dialog::instance().save("Save Sprite...", Asset::getExtensionByType(Asset::Type::Sprite), [](const std::filesystem::path& filename) -> void
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
}
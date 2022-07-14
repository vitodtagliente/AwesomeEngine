#include "sprite_animation_menu_item.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/editor/dialog.h>

namespace editor
{
	void SpriteAnimationMenuItem::execute()
	{
		Dialog::instance().save("Save Sprite Animation...", Asset::getExtensionByType(Asset::Type::SpriteAnimation), [](const std::filesystem::path& filename) -> void
			{
				if (!filename.string().empty())
				{
					SpriteAnimationAsset::data_t animation;
					animation.save(filename);

					AssetImporter importer;
					importer.import(filename);
				}
			}
		);
	}

	REFLECT_MENU_ITEM(SpriteAnimationMenuItem)
}
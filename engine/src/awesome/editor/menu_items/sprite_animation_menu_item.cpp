#include "sprite_animation_menu_item.h"

#include <filesystem>

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/sprite_animation.h>

namespace editor
{
	void SpriteAnimationMenuItem::render()
	{
		m_saveFileDialog.render();
	}

	void SpriteAnimationMenuItem::execute()
	{
		m_saveFileDialog.open("Save Sprite Animation...", Asset::getExtensionByType(Asset::Type::SpriteAnimation), [](const std::filesystem::path& filename) -> void
			{
				if (!filename.string().empty())
				{
					SpriteAnimation animation;
					animation.save(filename);

					AssetImporter importer;
					importer.import(filename);
				}
			}
		);
	}

	REFLECT_MENU_ITEM(SpriteAnimationMenuItem)
}
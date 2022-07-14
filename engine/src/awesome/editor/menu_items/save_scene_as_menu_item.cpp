#include "save_scene_as_menu_item.h"

#include <awesome/asset/asset.h>
#include <awesome/editor/dialog.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SaveSceneAsMenuItem::execute()
	{
		Dialog::instance().save("Save Scene as...", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
			{
				if (!path.string().empty())
				{
					World::instance().save(path);
				}
			}
		);
	}

	REFLECT_MENU_ITEM(SaveSceneAsMenuItem)
}
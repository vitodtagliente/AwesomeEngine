#include "save_scene_as_menu_item.h"

#include <awesome/data/archive.h>
#include <awesome/asset/asset.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SaveSceneAsMenuItem::render()
	{
		m_saveFileDialog.render();
	}

	void SaveSceneAsMenuItem::execute()
	{
		m_saveFileDialog.open("Save Scene as...", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
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
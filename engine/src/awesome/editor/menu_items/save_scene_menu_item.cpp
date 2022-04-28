#include "save_scene_menu_item.h"

#include <awesome/data/archive.h>
#include <awesome/asset/asset.h>
#include <awesome/asset/asset_importer.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SaveSceneMenuItem::render()
	{
		m_saveFileDialog.render();
	}

	void SaveSceneMenuItem::execute()
	{
		m_saveFileDialog.open("Save Scene", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& filename) -> void
			{
				if (!filename.string().empty())
				{
					Archive archive(filename, Archive::Mode::Write);
					archive << json::Serializer::to_string(World::instance().serialize());

					AssetImporter importer;
					importer.import(filename);
				}
			}
		);
	}

	REFLECT_MENU_ITEM(SaveSceneMenuItem)
}
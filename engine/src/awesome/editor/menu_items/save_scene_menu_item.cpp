#include "save_scene_menu_item.h"

#include <awesome/data/archive.h>
#include <awesome/asset/asset.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/scene_asset.h>
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
		World& world = World::instance();
		if (world.getLoadedSceneId() != uuid::Invalid)
		{
			SceneAssetPtr asset = AssetLibrary::instance().find<SceneAsset>(world.getLoadedSceneId());
			if (asset)
			{
				world.save(asset->descriptor.getDataPath());
				return;
			}
		}

		m_saveFileDialog.open("Save Scene", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
			{
				if (!path.string().empty())
				{
					World::instance().save(path);
				}
			}
		);
	}

	REFLECT_MENU_ITEM(SaveSceneMenuItem)
}
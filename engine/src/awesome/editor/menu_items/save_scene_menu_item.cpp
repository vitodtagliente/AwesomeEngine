#include "save_scene_menu_item.h"

#include <awesome/asset/asset.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/editor/dialog.h>
#include <awesome/entity/world.h>

namespace editor
{
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

		Dialog::instance().save("Save Scene", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
			{
				if (!path.string().empty())
				{
					World::instance().save(path);
				}
			}
		);
	}
}
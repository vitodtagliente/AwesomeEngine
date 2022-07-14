#include "scene_inspector.h"

#include <awesome/asset/scene_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

namespace editor
{
	bool SceneInspector::canInspect(const AssetPtr& asset)
	{
		return asset->descriptor.type == Asset::Type::Scene;
	}

	void SceneInspector::inspect(const AssetPtr& asset)
	{
		SceneAssetPtr scene = std::static_pointer_cast<SceneAsset>(asset);
		if (scene == nullptr)
		{
			return;
		}

		if (!scene->data.has_value())
		{
			Layout::text("Loading...");
			return;
		}

		if (Layout::button("Import"))
		{
			World::instance().load(scene);
		}
	}
}
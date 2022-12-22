#include "scene_asset_inspector.h"

#include <awesome/asset/scene_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>


bool SceneAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->descriptor.type == Asset::Type::Scene;
}

void SceneAssetInspector::inspect(const AssetPtr& asset)
{
	SceneAssetPtr scene = std::static_pointer_cast<SceneAsset>(asset);

	if (Layout::button("Import"))
	{
		World::instance().load(scene);
	}
}
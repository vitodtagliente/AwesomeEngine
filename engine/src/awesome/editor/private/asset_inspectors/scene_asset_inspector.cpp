#include "scene_asset_inspector.h"

#include <awesome/asset/scene_asset.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/entity/world.h>


bool SceneAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->getTypeName() == __SceneAssetType::type().name;
}

void SceneAssetInspector::inspect(const AssetPtr& asset)
{
	SceneAssetPtr scene = std::static_pointer_cast<SceneAsset>(asset);

	Layout::text(scene->data["description"].as_string());

	if (Layout::button(TextIcon::upload(" Load Scene")))
	{
		World::instance().load(scene);
	}
}
#include "scene_asset_inspector.h"

#include <awesome/asset/scene_asset.h>
#include <awesome/editor/text_icon.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/scene/scene_graph.h>

bool SceneAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->type == AssetType_Scene;
}

void SceneAssetInspector::inspect(const AssetPtr& asset)
{
	std::shared_ptr<SceneAsset> scene = std::static_pointer_cast<SceneAsset>(asset);
	
	if (FormLayout::button(TextIcon::upload(" Load Scene").c_str()))
	{
		SceneGraph::instance().load(scene);
	}
}
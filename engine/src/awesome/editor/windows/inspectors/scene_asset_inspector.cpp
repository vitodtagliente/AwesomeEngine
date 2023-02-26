#include "scene_asset_inspector.h"

bool SceneAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->type == AssetType_Scene;
}

void SceneAssetInspector::inspect(const AssetPtr& asset)
{
	// SceneAssetPtr scene = std::static_pointer_cast<SceneAsset>(asset);
	// 
	// if (Layout::button(TextIcon::upload(" Load Scene")))
	// {
	// 	World::instance().load(scene);
	// }
	// 
	// Layout::sameLine();
	// 
	// if (Layout::button(TextIcon::save(" Save")))
	// {
	// 	scene->save(scene->path);
	// }
	// 
	// Layout::separator();
	// Layout::input(*scene->data.settings);
	// Layout::inputMultiline("Note", scene->data.note);
}
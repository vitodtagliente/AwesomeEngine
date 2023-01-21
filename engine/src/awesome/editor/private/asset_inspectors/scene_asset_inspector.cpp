#include "scene_asset_inspector.h"

#include <awesome/asset/scene_asset.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/color.h>


bool SceneAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->getTypeName() == SceneAsset::staticTypeName();
}

void SceneAssetInspector::inspect(const AssetPtr& asset)
{
	SceneAssetPtr scene = std::static_pointer_cast<SceneAsset>(asset);

	if (Layout::button(TextIcon::upload(" Load Scene")))
	{
		World::instance().load(scene);
	}

	Layout::sameLine();

	if (Layout::button(TextIcon::save(" Save"), graphics::Color(1.f, .7f, .4f)))
	{
		scene->save(scene->path);
	}

	Layout::separator();
	Layout::input(*scene->data.settings);
	Layout::inputMultiline("Note", scene->data.note);
}
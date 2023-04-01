#include "prefab_asset_inspector.h"

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/widgets/entity_layout.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

bool PrefabAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->type == AssetType_Prefab;
}

void PrefabAssetInspector::inspect(const AssetPtr& asset)
{
	std::shared_ptr<PrefabAsset> prefab = std::static_pointer_cast<PrefabAsset>(asset);
	
	if (FormLayout::button(TextIcon::upload(" Import Prefab").c_str()))
	{
		SceneGraph::instance().root()->addChild(std::make_unique<Entity>(prefab->data.entity));
	}

	FormLayout::sameLine();

	if (FormLayout::button(TextIcon::save(" Save").c_str()))
	{
		prefab->save(prefab->path);
	}

	FormLayout::separator();

	EntityLayout::input(prefab->data.entity);
}
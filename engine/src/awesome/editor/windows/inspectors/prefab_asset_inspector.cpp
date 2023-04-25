#include "prefab_asset_inspector.h"

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/widgets/entity_layout.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

bool PrefabAssetInspector::canInspect(const AssetRecord& record)
{
	return record.type == AssetType_Prefab;
}

void PrefabAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = PrefabAsset(record.id);
		m_asset.load();
	}

	if (!m_asset.ready()) return;

	if (FormLayout::button(TextIcon::upload(" Import Prefab").c_str()))
	{
		SceneGraph::instance().root()->addChild(std::make_unique<Entity>(m_asset.resource->entity));
	}
	
	FormLayout::sameLine();
	
	if (FormLayout::button(TextIcon::save(" Save").c_str()))
	{
		// prefab->save(prefab->path);
	}
	
	FormLayout::separator();
	
	EntityLayout::input(m_asset.resource->entity);
}
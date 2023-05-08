#include "prefab_asset_inspector.h"

#include <awesome/editor/editor_ui.h>
#include <awesome/scene/scene_graph.h>

bool PrefabAssetInspector::canInspect(int type) const
{
	return type == AssetType_Prefab;
}

char* const PrefabAssetInspector::getTitle() const
{
	return "Prefab";
}

void PrefabAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = PrefabAsset(record.id);
		m_asset.load();
	}

	if (!m_asset.ready()) return;

	if (EditorUI::button((EditorUI::Icon::upload + " Import Prefab").c_str()))
	{
		SceneGraph::instance().root().addChild(std::make_unique<Entity>(m_asset.resource->entity));
	}
	
	EditorUI::sameLine();
	
	if (EditorUI::button((EditorUI::Icon::save + " Save").c_str()))
	{
		m_asset.save();
	}
	
	EditorUI::separator();
	EditorUI::input(m_asset.resource->entity);
}
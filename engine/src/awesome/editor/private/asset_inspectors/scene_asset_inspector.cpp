#include "scene_asset_inspector.h"

#include <awesome/editor/editor_ui.h>
#include <awesome/scene/scene_graph.h>

bool SceneAssetInspector::canInspect(int type) const
{
	return type == AssetType_Scene;
}

char* const SceneAssetInspector::getTitle() const
{
	return "Scene";
}

void SceneAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = SceneAsset(record.id);
		m_asset.load();
	}

	if (!m_asset.ready()) return;

	if (EditorUI::button((EditorUI::Icon::upload + " Load Scene").c_str()))
	{
		SceneGraph::instance().load(m_asset);
	}
}
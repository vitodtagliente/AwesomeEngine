#include "prefab_asset_inspector.h"

#include <awesome/data/archive.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/entity/world.h>
#include <awesome/editor/text_icon.h>
#include <awesome/encoding/json.h>

bool PrefabAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->descriptor.type == Asset::Type::Prefab;
}

void PrefabAssetInspector::inspect(const AssetPtr& asset)
{
	PrefabAssetPtr prefab = std::static_pointer_cast<PrefabAsset>(asset);
	
	if (prefab != m_previouslySelectedPrefab)
	{
		m_previouslySelectedPrefab = prefab;
		m_entity.deserialize(prefab->data.value());
	}

	if (Layout::button(TextIcon::upload(" Import Prefab")))
	{
		World::instance().spawn(prefab);
	}

	Layout::separator();

	EntityLayout::input(&m_entity);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		const json::value& data = m_entity.serialize();
		prefab->data = data;
		Archive archive(prefab->descriptor.getDataPath(), Archive::Mode::Write);
		archive << json::Serializer::to_string(data);
	}
}
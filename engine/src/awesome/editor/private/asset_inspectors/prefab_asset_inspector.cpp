#include "prefab_asset_inspector.h"

#include <awesome/core/serialization.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/editor/text_icon.h>

PrefabAssetInspector::~PrefabAssetInspector()
{
	delete m_entity;
}

bool PrefabAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->getTypeName() == PrefabAsset::staticTypeName();
}

void PrefabAssetInspector::inspect(const AssetPtr& asset)
{
	PrefabAssetPtr prefab = std::static_pointer_cast<PrefabAsset>(asset);
	
	if (prefab != m_previouslySelectedPrefab)
	{
		m_previouslySelectedPrefab = prefab;
		if (m_entity != nullptr)
		{
			delete m_entity;
		}
		m_entity = Entity::load(prefab);
	}

	if (Layout::button(TextIcon::upload(" Import Prefab")))
	{
		World::instance().instantiate(prefab);
	}

	Layout::separator();

	EntityLayout::input(m_entity);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		prefab->data = Serializer::serialize(*m_entity);
		prefab->save(prefab->path);
	}
}
#include "prefab_inspector.h"

#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/entity/world.h>
#include <awesome/editor/text_icon.h>
#include <awesome/encoding/json.h>

namespace editor
{
	bool PrefabInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->descriptor.type == Asset::Type::Prefab;
	}

	void PrefabInspector::inspect(const State::Selection& selection)
	{
		PrefabAssetPtr prefab = std::static_pointer_cast<PrefabAsset>(selection.asAsset());
		if (prefab == nullptr || !prefab->data.has_value())
		{
			return;
		}
		
		if (prefab != m_previouslySelectedPrefab)
		{
			m_previouslySelectedPrefab = prefab;
			m_entity.deserialize(prefab->data.value());
		}

		if (Layout::button(TextIcon::upload(" Import Prefab")))
		{
			Entity* const entity = World::instance().spawn();
			Entity::duplicate(prefab, *entity);
		}

		Layout::separator();

		EntityLayout::input(m_entity);

		Layout::separator();

		if (Layout::button(TextIcon::save(" Save")))
		{
			prefab->data.value() = json::Serializer::to_string(m_entity.serialize());
		}
	}
}
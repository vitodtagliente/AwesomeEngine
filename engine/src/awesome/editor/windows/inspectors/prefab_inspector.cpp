#include "prefab_inspector.h"

#include <awesome/data/prefab_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

#include "entity_layout.h"

namespace editor
{
	bool PrefabInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Prefab;
	}

	void PrefabInspector::inspect(const State::Selection& selection, const std::filesystem::path&)
	{
		PrefabAssetPtr prefab = std::static_pointer_cast<PrefabAsset>(selection.asAsset());
		if (prefab == nullptr)
		{
			return;
		}

		if (Layout::button("Import Prefab"))
		{
			World::instance().spawn(prefab->data.entity);
		}

		Layout::separator();

		Entity& entity = prefab->data.entity;
		EntityLayout::input(entity);

		Layout::separator();

		if (Layout::button("Save"))
		{
			prefab->data.save(prefab->filename.parent_path() / prefab->filename.stem());
		}
	}
}
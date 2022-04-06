#include "prefab_inspector.h"

#include <awesome/data/prefab_asset.h>
#include <awesome/editor/layout.h>

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

		if (Layout::button("Import"))
		{

		}


	}
}
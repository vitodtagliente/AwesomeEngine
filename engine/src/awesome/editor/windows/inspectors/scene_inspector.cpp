#include "scene_inspector.h"

#include <awesome/data/scene_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/world.h>

namespace editor
{
	bool SceneInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->descriptor.type == Asset::Type::Scene;
	}

	void SceneInspector::inspect(const State::Selection& selection)
	{
		SceneAssetPtr asset = std::static_pointer_cast<SceneAsset>(selection.asAsset());
		if (asset == nullptr || !asset->data.has_value())
		{
			return;
		}

		if (Layout::button("Import"))
		{
			World::instance().load(asset);
		}
	}
}
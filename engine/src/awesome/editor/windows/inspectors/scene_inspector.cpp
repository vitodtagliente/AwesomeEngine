#include "scene_inspector.h"

#include <awesome/data/scene_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/world.h>

namespace editor
{
	bool SceneInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Scene;
	}

	void SceneInspector::inspect(const State::Selection& selection, const std::filesystem::path&)
	{
		SceneAssetPtr asset = std::static_pointer_cast<SceneAsset>(selection.asAsset());
		if (asset == nullptr)
		{
			return;
		}

		if (Layout::button("Import"))
		{
			World::instance().deserialize(json::Deserializer::parse(asset->data));
		}
	}
}
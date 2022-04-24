/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/data/prefab_asset.h>
#include <awesome/editor/windows/inspector_window.h>
#include <awesome/entity/entity.h>

namespace editor
{
	class PrefabInspector : public InspectorWindow::Inspector
	{
	public:
		PrefabInspector() = default;

		virtual bool canInspect(const State::Selection& selection) override;
		virtual void inspect(const State::Selection& selection) override;

	private:
		Entity m_entity;
		PrefabAssetPtr m_previouslySelectedPrefab;
	};
}
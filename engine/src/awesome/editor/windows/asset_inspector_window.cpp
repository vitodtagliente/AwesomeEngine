#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

#include <awesome/editor/windows/inspectors/image_inspector.h>
#include <awesome/editor/windows/inspectors/prefab_inspector.h>
#include <awesome/editor/windows/inspectors/scene_inspector.h>
#include <awesome/editor/windows/inspectors/sprite_animation_inspector.h>
#include <awesome/editor/windows/inspectors/sprite_inspector.h>
#include <awesome/editor/windows/inspectors/text_inspector.h>

namespace editor
{
	void AssetInspectorWindow::init()
	{
		m_inspectors.push_back(std::make_unique<ImageInspector>());
		m_inspectors.push_back(std::make_unique<PrefabInspector>());
		m_inspectors.push_back(std::make_unique<SceneInspector>());
		m_inspectors.push_back(std::make_unique<SpriteAnimationInspector>());
		m_inspectors.push_back(std::make_unique<SpriteInspector>());
		m_inspectors.push_back(std::make_unique<TextInspector>());
	}

	void AssetInspectorWindow::render()
	{
		AssetPtr asset = State::instance().selection.asset;
		if (asset)
		{
			Layout::text(asset->descriptor.path.filename().string());
			Layout::text(enumToString(asset->descriptor.type));
			Layout::separator();
			for (const auto& inspector : m_inspectors)
			{
				if (inspector->canInspect(asset))
				{
					inspector->inspect(asset);
					break;
				}
			}
		}
	}

	void AssetInspectorWindow::update(const double deltaTime)
	{
		const State& state = State::instance();
		if (state.selection.asset)
		{
			for (const auto& inspector : m_inspectors)
			{
				if (inspector->canInspect(state.selection.asset))
				{
					inspector->update(state.selection.asset, deltaTime);
					break;
				}
			}
		}
	}

	REFLECT_WINDOW(AssetInspectorWindow);
}
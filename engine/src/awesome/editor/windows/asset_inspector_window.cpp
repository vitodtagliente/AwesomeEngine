#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/editor/editor.h>
#include <awesome/editor/editor_ui.h>
#include <awesome/graphics/color.h>

#include <awesome/editor/asset_inspectors/image_asset_inspector.h>
#include <awesome/editor/asset_inspectors/prefab_asset_inspector.h>
#include <awesome/editor/asset_inspectors/scene_asset_inspector.h>
#include <awesome/editor/asset_inspectors/sprite_animation_asset_inspector.h>

AssetInspectorWindow::AssetInspectorWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
}

char* const AssetInspectorWindow::getTitle() const
{
	return "Asset Inspector";
}

void AssetInspectorWindow::init()
{
	m_inspectors.push_back(std::make_unique<ImageAssetInspector>());
	m_inspectors.push_back(std::make_unique<PrefabAssetInspector>());
	m_inspectors.push_back(std::make_unique<SceneAssetInspector>());
	m_inspectors.push_back(std::make_unique<SpriteAnimationAssetInspector>());

	for (const auto& [name, options] : TypeFactory::list("Type", "AssetInspector"))
	{
		std::unique_ptr<AssetInspector> inspector = std::unique_ptr<AssetInspector>(TypeFactory::instantiate<AssetInspector>(name));
		if (inspector != nullptr)
		{
			m_inspectors.push_back(std::move(inspector));
		}
	}
}

void AssetInspectorWindow::render()
{
	static const graphics::Color s_filenameColor(0.f, 0.6f, 0.6f);
	static const graphics::Color s_assetTypeColor(1.f, 0.6f, 0.6f);

	if (m_editorState->selection.asset.has_value())
	{
		const AssetRecord& record = m_editorState->selection.asset.value();

		for (const auto& inspector : m_inspectors)
		{
			if (inspector->canInspect(record.type))
			{
				const std::string title = inspector->getTitle();
				EditorUI::button(title.empty() ? "Asset" : title.c_str(), s_assetTypeColor);
				EditorUI::sameLine();
				if (EditorUI::button(record.path.filename().string().c_str(), s_filenameColor))
				{
					m_editorState->select(record.path);
				}
				EditorUI::separator();
				inspector->inspect(record);
				return;
			}
		}

		// no inspector found
		EditorUI::button("Asset", s_assetTypeColor);
		EditorUI::sameLine();
		if (EditorUI::button(record.path.filename().string().c_str(), s_filenameColor))
		{
			m_editorState->select(record.path);
		}
		EditorUI::separator();
		EditorUI::text("Cannot inspect the selected asset");
	}
}

void AssetInspectorWindow::update(const double deltaTime)
{
	if (m_editorState->selection.asset.has_value())
	{
		const AssetRecord& record = m_editorState->selection.asset.value();

		for (const auto& inspector : m_inspectors)
		{
			if (inspector->canInspect(record.type))
			{				
				inspector->update(deltaTime);
				return;
			}
		}
	}
}

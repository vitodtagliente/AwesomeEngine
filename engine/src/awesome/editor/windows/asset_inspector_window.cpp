#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/editor/editor.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/graphics/color.h>

#include "inspectors/image_asset_inspector.h"
#include "inspectors/prefab_asset_inspector.h"
#include "inspectors/scene_asset_inspector.h"

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
	// m_inspectors.push_back(std::make_unique<SpriteAnimationAssetInspector>());
	// m_inspectors.push_back(std::make_unique<TextAssetInspector>());
	// m_inspectors.push_back(std::make_unique<TilesetAssetInspector>());
}

void AssetInspectorWindow::render()
{
	static const graphics::Color s_filenameColor(0.f, 0.6f, 0.6f);
	static const graphics::Color s_assetTypeColor(1.f, 0.6f, 0.6f);

	AssetPtr asset = m_editorState->selection.asset;
	if (asset != nullptr)
	{
		FormLayout::button("", s_assetTypeColor);
		FormLayout::sameLine();
		if (FormLayout::button(asset->path.filename().string().c_str(), s_filenameColor))
		{
			m_editorState->select(asset->path);
		}
		for (const auto& inspector : m_inspectors)
		{
			if (!inspector->canInspect(asset)) continue;

			if(asset->state == Asset::State::Ready)
			{
				inspector->inspect(asset);
			}
			else
			{
				FormLayout::text("Asset loading...");
			}
			break;
		}
	}
}

void AssetInspectorWindow::update(const double deltaTime)
{
	AssetPtr asset = m_editorState->selection.asset;
	if (asset != nullptr && asset->state == Asset::State::Ready)
	{
		for (const auto& inspector : m_inspectors)
		{
			if (inspector->canInspect(asset))
			{
				inspector->update(asset, deltaTime);
				break;
			}
		}
	}
}
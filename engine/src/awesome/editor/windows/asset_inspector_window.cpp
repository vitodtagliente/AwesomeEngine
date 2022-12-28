#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/editor/editor.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/asset_inspectors/asset_inspectors.h>
#include <awesome/graphics/color.h>

void AssetInspectorWindow::init()
{
	m_inspectors.push_back(std::make_unique<ImageAssetInspector>());
	m_inspectors.push_back(std::make_unique<PrefabAssetInspector>());
	m_inspectors.push_back(std::make_unique<SceneAssetInspector>());
	m_inspectors.push_back(std::make_unique<SpriteAnimationAssetInspector>());
	m_inspectors.push_back(std::make_unique<SpriteAssetInspector>());
	m_inspectors.push_back(std::make_unique<TextAssetInspector>());
	m_inspectors.push_back(std::make_unique<TilesetAssetInspector>());
}

void AssetInspectorWindow::render()
{
	static const graphics::Color s_filenameColor(0.f, 0.6f, 0.6f);
	static const graphics::Color s_assetTypeColor(1.f, 0.6f, 0.6f);

	AssetPtr asset = Editor::instance().state.selection.asset;
	if (asset != nullptr)
	{
		if (Layout::button(asset->descriptor.path.filename().string(), s_filenameColor))
		{
			Editor::instance().state.select(asset->descriptor.path);
		}
		Layout::button(enumToString(asset->descriptor.type), s_assetTypeColor);
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
	AssetPtr asset = Editor::instance().state.selection.asset;
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
#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

#include <awesome/editor/private/asset_inspectors/asset_inspectors.h>

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
	AssetPtr asset = State::instance().selection.asset;
	if (asset != nullptr)
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
	AssetPtr asset = State::instance().selection.asset;
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
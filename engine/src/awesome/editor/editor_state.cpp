#include "editor_state.h"

#include <assert.h>

#include <awesome/asset/asset_database.h>
#include <awesome/asset/asset_library.h>
#include <awesome/scene/entity.h>

#include "windows/asset_inspector_window.h"
#include "windows/content_browser_window.h"
#include "windows/entity_inspector_window.h"
#include "windows/log_window.h"
#include "windows/performance_window.h"
#include "windows/scene_window.h"
#include "windows/settings_window.h"
#include "windows/sprite_editor_window.h"
#include "windows/stress_window.h"

EditorState::EditorState()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void EditorState::init()
{
	settings.load(AssetLibrary::instance().path() / EditorSettings::Filename);

	m_windows.push_back(std::make_unique<AssetInspectorWindow>());
	m_windows.push_back(std::make_unique<ContentBrowserWindow>());
	m_windows.push_back(std::make_unique<EntityInspectorWindow>());
	m_windows.push_back(std::make_unique<LogWindow>());
	m_windows.push_back(std::make_unique<PerformanceWindow>());
	m_windows.push_back(std::make_unique<SceneWindow>());
	m_windows.push_back(std::make_unique<SettingsWindow>());
	m_windows.push_back(std::make_unique<SpriteEditorWindow>());
	m_windows.push_back(std::make_unique<StressWindow>());

	for (const auto& [name, options] : TypeFactory::list("Type", "Window"))
	{
		std::unique_ptr<Window> window = std::unique_ptr<Window>(TypeFactory::instantiate<Window>(name));
		if (window != nullptr)
		{
			m_windows.push_back(std::move(window));
		}
	}

	std::map<std::string, bool>visibility;
	for (const auto& window : m_windows)
	{
		window->init();

		const std::string& title = window->getTitle();
		const auto& it = settings.windowsVisibility.find(title);
		if (it != settings.windowsVisibility.end())
		{
			window->visible = it->second;
			visibility.insert(std::make_pair(title, window->visible));
		}
		else
		{
			visibility.insert(std::make_pair(title, true));
		}
	}

	// clean up deprecated windows
	settings.windowsVisibility = visibility;
	settings.save();
}

void EditorState::uninit()
{
	reset();
	for (std::vector<std::unique_ptr<Window>>::reverse_iterator it = m_windows.rbegin(); it != m_windows.rend(); ++it)
	{
		(*it)->uninit();
	}
	m_windows.clear();
}

void EditorState::select(const AssetRecord& asset)
{
	if (selection.asset.has_value()
		&& *selection.asset == asset) return;

	selection.asset = asset;
	onSelectedAssetChanged.invoke(asset);
}

void EditorState::select(Control* const control)
{
	if (selection.control == control) return;

	selection.control = control;
	onSelectedControlChanged.invoke(control);
}

void EditorState::select(Entity* const entity)
{
	if (selection.entity == entity) return;

	selection.entity = entity;
	onSelectedEntityChanged.invoke(entity);
}

void EditorState::select(const std::filesystem::path& folder)
{
	if (folder == path) return;

	path = folder;
	onSelectedPathChanged.invoke(folder);
}

void EditorState::unselectAsset()
{
	selection.asset.reset();
}

void EditorState::unselectControl()
{
	selection.control = nullptr;
}

void EditorState::unselectEntity()
{
	selection.entity = nullptr;
}

void EditorState::reset()
{
	selection.asset.reset();
	selection.control = nullptr;
	selection.entity = nullptr;
}

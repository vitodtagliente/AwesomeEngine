#include "editor_state.h"

#include <assert.h>

EditorState* EditorState::s_instance{ nullptr };

EditorState::EditorState()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void EditorState::select(const AssetPtr& asset)
{
	if (selection.asset == asset) return;

	static const size_t s_maxHistory{ 10 };

	selection.asset = asset;
	if (m_history.size() == s_maxHistory)
	{
		m_history.pop();
	}
	m_history.push(asset);

	onSelectedAssetChanged.broadcast(asset);
}

void EditorState::select(Entity* const entity)
{
	if (selection.entity == entity) return;

	selection.entity = entity;

	onSelectedEntityChanged.broadcast(entity);
}

void EditorState::select(const std::filesystem::path& folder)
{
	if (folder == path) return;

	path = folder;
	onSelectedPathChanged.broadcast(folder);
}

void EditorState::unselectAsset()
{
	selection.asset = nullptr;
}

void EditorState::unselectEntity()
{
	selection.entity = nullptr;
}
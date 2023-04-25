#include "editor_state.h"

#include <assert.h>

#include <awesome/asset/asset_database.h>
#include <awesome/scene/entity.h>

EditorState* EditorState::s_instance{ nullptr };

EditorState::EditorState()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void EditorState::select(AssetRecord* const asset)
{
	if (selection.asset == asset) return;

	selection.asset = asset;
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

void EditorState::reset()
{
	selection.asset = nullptr;
	selection.entity = nullptr;
}

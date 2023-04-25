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

void EditorState::select(const AssetRecord& asset)
{
	if (selection.asset.has_value() 
		&& *selection.asset == asset) return;

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
	selection.asset.reset();
}

void EditorState::unselectEntity()
{
	selection.entity = nullptr;
}

void EditorState::reset()
{
	selection.asset.reset();
	selection.entity = nullptr;
}

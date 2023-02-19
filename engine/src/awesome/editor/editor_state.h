/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <queue>

#include <awesome/asset/asset.h>
#include <awesome/core/event.h>

class EditorState
{
public:
	struct Selection
	{
		AssetPtr asset;
		class Entity* entity{ nullptr };
	};

	EditorState();

	static EditorState* const instance() { return s_instance; }

	void select(const AssetPtr& asset);
	void select(class Entity* const entity);
	void select(const std::filesystem::path& path);
	void unselectAsset();
	void unselectEntity();

	std::filesystem::path path;
	Selection selection;

	// events
	event_t<AssetPtr> onSelectedAssetChanged;
	event_t<Entity*> onSelectedEntityChanged;
	event_t<std::filesystem::path> onSelectedPathChanged;

private:
	std::queue<AssetPtr> m_history;

	static EditorState* s_instance;
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <optional>

#include <awesome/asset/asset_database.h>
#include <awesome/core/event.h>

class Entity;

class EditorState
{
public:
	struct Selection
	{
		std::optional<AssetRecord> asset;
		Entity* entity{ nullptr };
	};

	EditorState();

	static EditorState* const instance() { return s_instance; }

	void select(const AssetRecord& asset);
	void select(Entity* const entity);
	void select(const std::filesystem::path& path);
	void unselectAsset();
	void unselectEntity();
	void reset();

	std::filesystem::path path;
	Selection selection;

	// events
	event_t<const AssetRecord&> onSelectedAssetChanged;
	event_t<Entity*> onSelectedEntityChanged;
	event_t<std::filesystem::path> onSelectedPathChanged;

private:
	static EditorState* s_instance;
};
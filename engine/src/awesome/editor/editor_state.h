/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <awesome/core/event.h>

struct AssetRecord;
class Entity;

class EditorState
{
public:
	struct Selection
	{
		AssetRecord* asset{ nullptr };
		Entity* entity{ nullptr };
	};

	EditorState();

	static EditorState* const instance() { return s_instance; }

	void select(AssetRecord* const asset);
	void select(Entity* const entity);
	void select(const std::filesystem::path& path);
	void unselectAsset();
	void unselectEntity();
	void reset();

	std::filesystem::path path;
	Selection selection;

	// events
	event_t<AssetRecord*> onSelectedAssetChanged;
	event_t<Entity*> onSelectedEntityChanged;
	event_t<std::filesystem::path> onSelectedPathChanged;

private:
	static EditorState* s_instance;
};
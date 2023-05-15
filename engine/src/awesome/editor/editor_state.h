/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <optional>

#include <awesome/asset/asset_database.h>
#include <awesome/core/event.h>

#include "editor_settings.h"
#include "window.h"

class Control;
class Entity;

class EditorState
{
public:
	struct Selection
	{
		std::optional<AssetRecord> asset;
		Control* control{ nullptr };
		Entity* entity{ nullptr };
	};

	EditorState();

	void init();

	static EditorState* const instance() { return s_instance; }

	const std::vector<std::unique_ptr<Window>>& getWindows() const { return m_windows; }

	void select(const AssetRecord& asset);
	void select(Control* const control);
	void select(Entity* const entity);
	void select(const std::filesystem::path& path);
	void unselectAsset();
	void unselectControl();
	void unselectEntity();
	void reset();

	std::filesystem::path path;
	Selection selection;
	EditorSettings settings;

	// events
	event_t<const AssetRecord&> onSelectedAssetChanged;
	event_t<Control*> onSelectedControlChanged;
	event_t<Entity*> onSelectedEntityChanged;
	event_t<std::filesystem::path> onSelectedPathChanged;

private:
	std::vector<std::unique_ptr<Window>> m_windows;

	static EditorState* s_instance;
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/asset/asset_library.h>
#include <awesome/data/directory.h>
#include <awesome/editor/window.h>

#include "content_browser_window_generated.h"

CLASS(Category = Window)
class ContentBrowserWindow : public Window
{
public:
	ContentBrowserWindow() = default;

	std::string getTitle() const override { return "Content Browser"; }
	virtual void render() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:

	void processInput(const std::filesystem::path& path);

	void addFolder();
	std::string decorateFile(const std::filesystem::path& file);
	void deleteFile(const std::filesystem::path& path);
	void importFile(const std::filesystem::path& file);
	void moveFile(const std::filesystem::path& from, const std::filesystem::path& to);
	void refreshDirectory();
	void renameFile(const std::filesystem::path& path, const std::string& name);
	void selectFile(const std::filesystem::path& file);

	enum class NavigationState
	{
		Navigating,
		Renaming
	};

	Directory m_directory{ Directory::scan(AssetLibrary::instance().getDirectory(), Directory::ScanSettings(Asset::Extension, false))};
	std::string m_filter;
	std::filesystem::path m_root{ AssetLibrary::instance().getDirectory() };
	std::filesystem::path m_selectedItem;
	NavigationState m_state{ NavigationState::Navigating };
	std::string m_tempRename;
};
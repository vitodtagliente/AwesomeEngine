/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/data/directory.h>
#include <awesome/editor/window.h>

#include "content_browser_window_generated.h"

CLASS(Type = Window)
class ContentBrowserWindow : public Window
{
public:
	ContentBrowserWindow() = default;

	virtual std::string getTitle() const override;
	virtual void init() override;
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

	Directory m_directory;
	std::string m_filter;
	std::filesystem::path m_root;
	std::filesystem::path m_selectedItem;
	NavigationState m_state{ NavigationState::Navigating };
	std::string m_tempRename;
};
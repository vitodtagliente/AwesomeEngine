/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <optional>

#include <awesome/data/directory.h>
#include <awesome/editor/window.h>

class ContentBrowserWindow : public Window
{
public:
	ContentBrowserWindow();

	virtual char* const getTitle() const override;
	virtual void init() override;
	virtual void render() override;
	virtual void update(double deltaTime) override;

	void queue_refresh();

	static ContentBrowserWindow* const instance() { return s_instance; }

private:
	void addNewFolder(const std::string& name);
	std::string decorateFile(const std::filesystem::path& file);
	void deleteFile(const std::filesystem::path& path);
	void moveFile(const std::filesystem::path& from, const std::filesystem::path& to);
	void renameFile(const std::filesystem::path& path, const std::string& name);

	enum class NavigationState
	{
		Navigating,
		Renaming
	};

	Directory m_directory;
	class EditorState* m_editorState;
	std::string m_filter;
	bool m_refresh{ false };
	std::filesystem::path m_root;
	std::optional<std::filesystem::path> m_selectedItem;
	NavigationState m_state{ NavigationState::Navigating };
	std::string m_tempRename;

	static inline ContentBrowserWindow* s_instance{ nullptr };
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/menu_item.h>
#include <awesome/editor/widgets/context_menu.h>
#include <awesome/editor/widgets/open_file_dialog.h>
#include <awesome/editor/window.h>
#include <awesome/editor/utils/dir.h>

namespace editor
{
	class ContentBrowserWindow : public Window
	{
	public:
		ContentBrowserWindow() = default;

		std::string getTitle() const override { return "Content Browser"; }
		virtual void init() override;
		virtual void render() override;
		virtual void update(double deltaTime) override;

		REFLECT()

	private:

		void processInput(const std::filesystem::path& path);

		void addFolder();
		std::string decorateFile(const std::filesystem::path& file);
		void deleteFile(const std::filesystem::path& path);
		void handleContextMenuInput(const std::string& name);
		void importFile(const std::filesystem::path& file);
		void moveFile(const std::filesystem::path& from, const std::filesystem::path& to);
		void refreshDirectory();
		void renameFile(const std::filesystem::path& path, const std::string& name);
		void selectFile(const std::filesystem::path& file);

		enum class NavigationState
		{
			ContextMenu,
			Navigating,
			Renaming
		};

		ContextMenu m_contextMenu;
		Dir m_dir{ AssetLibrary::instance().getDirectory() };
		std::string m_filter;
		std::vector<std::string> m_menuItemNames;
		std::vector<std::unique_ptr<MenuItem>> m_menuItems;
		OpenFileDialog m_openFileDialog;
		std::filesystem::path m_root{ AssetLibrary::instance().getDirectory() };
		std::filesystem::path m_selectedItem;
		NavigationState m_state{ NavigationState::Navigating };
		std::string m_tempRename;
	};
}
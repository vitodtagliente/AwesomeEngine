/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/window.h>
#include <awesome/editor/utils/dir.h>

namespace editor
{
	class ContentBrowserWindow : public Window
	{
	public:
		ContentBrowserWindow() = default;

		std::string getTitle() const override { return "Content Browser"; }
		virtual void render() override;
		virtual void update(double deltaTime) override;

		REFLECT()

	private:

		void processInput(const std::filesystem::path& path);
		void addFolder();
		void deleteFile(const std::filesystem::path& file);
		void selectFile(const std::filesystem::path& file);
		void renameFile(const std::filesystem::path& file, const std::string& name);
		void refreshDir();

		enum class NavigationState
		{
			Navigating,
			Renaming
		};

		Dir m_dir{ AssetLibrary::instance().getDirectory() };
		std::string m_filter;
		std::filesystem::path m_root{ AssetLibrary::instance().getDirectory() };
		std::filesystem::path m_selectedItem;
		NavigationState m_state{ NavigationState::Navigating };
		std::string m_tempRename;
	};
}
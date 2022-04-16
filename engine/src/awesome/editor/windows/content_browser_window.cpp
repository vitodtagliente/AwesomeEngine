#include "content_browser_window.h"

#include <regex>

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/icons.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

namespace editor
{
	void ContentBrowserWindow::render()
	{
		const bool hasActiveFocus = Layout::isWindowFocused();
		if (hasActiveFocus && !m_selectedItem.empty())
		{
			processInput(m_selectedItem);
		}

		if (Layout::button(ICON_FA_PLUS))
		{
			addFolder();
		}

		Layout::sameLine();

		const std::string previousFilter = m_filter;
		Layout::input(ICON_FA_SEARCH, m_filter);
		if (previousFilter != m_filter || !hasActiveFocus)
		{
			m_state = NavigationState::Navigating;
		}

		Layout::separator();

		for (const auto& file : m_dir.files)
		{
			const bool isSelected = m_selectedItem == file;
			if (isSelected && m_state == NavigationState::Renaming)
			{
				Layout::rename(m_tempRename);
			}
			else
			{
				const std::string name = file.stem().string();
				if (!m_filter.empty() && !StringUtil::contains(name, m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				bool select = false;
				if (std::filesystem::is_directory(file) && name != "..")
				{
					select = (Layout::selectable(name, isSelected, []() -> void
						{
							// m_dir = Dir(file);
							// State::instance().path = m_dir.path;
						}
					));
				}
				else
				{
					select = Layout::selectable(name, isSelected);
				}

				if (select)
				{
					m_state = NavigationState::Navigating;
					m_tempRename = name;
					selectFile(file);
				}
			}
		}
	}

	void ContentBrowserWindow::update(const double deltaTime)
	{
		m_dir.refreshTimer.tick(deltaTime);
		if (m_dir.refreshTimer.isExpired())
		{
			m_dir = Dir(m_dir.path);
		}
	}

	void ContentBrowserWindow::processInput(const std::filesystem::path& file)
	{
		Input& input = Input::instance();
		if (m_state == NavigationState::Renaming)
		{
			if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
			{
				m_state = NavigationState::Navigating;
				renameFile(file, m_tempRename);
			}
		}
		else
		{
			if (input.isKeyPressed(KeyCode::F2))
			{
				m_state = NavigationState::Renaming;
			}
			else if (input.isKeyPressed(KeyCode::Delete))
			{
				deleteFile(file);
			}
		}
	}

	void ContentBrowserWindow::addFolder()
	{
		static const std::string DefaultName{ "New Folder" };
		int i = 0;
		while (true)
		{
			std::filesystem::path path = m_dir.path / (DefaultName + ((i == 0) ? "" : std::string(" ") + std::to_string(i)));
			if (!std::filesystem::exists(path))
			{
				std::filesystem::create_directory(path);
				m_dir.refresh();
				break;
			}
			++i;
		}
	}

	void ContentBrowserWindow::deleteFile(const std::filesystem::path& file)
	{
		static const auto getAssetFilename = [](const std::filesystem::path& filename) -> std::string
		{
			return filename.string().substr(0, filename.string().length() - std::string(Asset::Extension).length());
		};

		AssetLibrary& library = AssetLibrary::instance();
		Asset descriptor = Asset::load(file);
		std::shared_ptr<Asset> asset = library.find(descriptor.id);
		if (asset)
		{
			library.unload(asset->id);
			library.remove(asset->id);

			std::filesystem::remove(file);
			std::filesystem::remove(getAssetFilename(file));
			m_dir.refresh();
		}
	}

	void ContentBrowserWindow::selectFile(const std::filesystem::path& file)
	{
		m_selectedItem = file;
		if (std::filesystem::is_directory(file))
		{
			if (m_dir.parent == file)
			{
				m_dir = Dir(file);
				State::instance().path = m_dir.path;
			}
			State::instance().select();
		}
		else
		{
			Asset descriptor = Asset::load(file);
			std::shared_ptr<Asset> asset = AssetLibrary::instance().find(descriptor.id);
			if (asset)
			{
				State::instance().select(asset);
			}
			else
			{
				State::instance().select();
			}
		}
	}

	void ContentBrowserWindow::renameFile(const std::filesystem::path& file, const std::string& name)
	{

		static const auto getAssetFilename = [](const std::filesystem::path& filename) -> std::string
		{
			return filename.string().substr(0, filename.string().length() - std::string(Asset::Extension).length());
		};

		static const auto renameAsset = [](const std::filesystem::path& filename, const std::string& renaming) -> std::string
		{
			std::filesystem::path name = filename.stem();
			while (name.has_extension())
			{
				name = name.stem();
			}

			std::filesystem::path rename = renaming;
			while (rename.has_extension())
			{
				rename = rename.stem();
			}

			return std::regex_replace(filename.string(), std::regex(name.string()), rename.string());
		};

		if (std::filesystem::is_directory(file))
		{
			std::filesystem::rename(file, file.parent_path() / name);
			m_dir.refresh();
		}
		else
		{
			AssetLibrary& library = AssetLibrary::instance();
			Asset descriptor = Asset::load(file);
			std::shared_ptr<Asset> asset = library.find(descriptor.id);
			if (asset)
			{
				const std::filesystem::path newAssetFilename = renameAsset(file, name);
				if (file != newAssetFilename)
				{
					std::filesystem::rename(file, newAssetFilename);
					std::filesystem::rename(getAssetFilename(file), renameAsset(getAssetFilename(file), name));
					m_dir.refresh();

					asset->filename = newAssetFilename;
					library.insert(*asset);
				}
			}
		}
	}

	ContentBrowserWindow::Dir::Dir(const std::filesystem::path& path)
		: files()
		, parent(path.parent_path())
		, path(path)
		, refreshTimer(10.0)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			const std::filesystem::path& file = entry.path();
			if (Asset::isAsset(file) || entry.is_directory())
			{
				files.push_back(file);
			}
		}
	}

	void ContentBrowserWindow::Dir::refresh()
	{
		refreshTimer.expire();
	}

	REFLECT_WINDOW(ContentBrowserWindow);
}
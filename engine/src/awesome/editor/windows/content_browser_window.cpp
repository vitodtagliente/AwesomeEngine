#include "content_browser_window.h"

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	void ContentBrowserWindow::render()
	{
		const bool hasActiveFocus = Layout::isWindowFocused();
		if (hasActiveFocus && !m_selectedItem.empty())
		{
			processInput(m_selectedItem);
		}

		if (Layout::button(TextIcon::plus()))
		{
			addFolder();
		}

		Layout::sameLine();

		const std::string previousFilter = m_filter;
		Layout::input(TextIcon::search(), m_filter);
		if (previousFilter != m_filter || !hasActiveFocus)
		{
			m_state = NavigationState::Navigating;
		}

		Layout::separator();

		if (m_dir.path != m_root && Layout::selectable("..", false))
		{
			m_state = NavigationState::Navigating;
			selectFile(m_dir.parent);
		}

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

				bool changeDirectory = false;
				if (std::filesystem::is_directory(file) && name != "..")
				{
					if (Layout::selectable(std::string(TextIcon::folder()) + " " + name, isSelected, [&changeDirectory]() -> void { changeDirectory = true; }))
					{
						m_state = NavigationState::Navigating;
						m_tempRename = name;
						selectFile(file);
					}
				}
				else if (Layout::selectable(name, isSelected))
				{
					m_state = NavigationState::Navigating;
					m_tempRename = name;
					selectFile(file);
				}

				if (changeDirectory)
				{
					m_dir = Dir(file);
					State::instance().path = m_dir.path;
					break;
				}
			}
		}
	}

	void ContentBrowserWindow::update(double deltaTime)
	{
		if (State::instance().hasPendingContentRefresh())
		{
			refreshDir();
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
				refreshDir();
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

		if (std::filesystem::is_directory(file))
		{
			std::filesystem::remove(file);
			
			State::instance().select();
			m_selectedItem.clear();
			
			refreshDir();
		}
		else
		{
			AssetLibrary& library = AssetLibrary::instance();
			Asset descriptor = Asset::load(file);
			std::shared_ptr<Asset> asset = library.find(descriptor.id);
			if (asset)
			{
				library.unload(asset->id);
				library.remove(asset->id);

				std::filesystem::remove(file);
				std::filesystem::remove(getAssetFilename(file));

				m_selectedItem.clear();
				State::instance().select();

				refreshDir();
			}
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

			return StringUtil::replace(filename.string(), name.string(), rename.string());
		};

		if (std::filesystem::is_directory(file))
		{
			std::filesystem::rename(file, file.parent_path() / name);
			refreshDir();
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
					refreshDir();

					asset->filename = newAssetFilename;
					library.insert(*asset);
				}
			}
		}
	}

	void ContentBrowserWindow::refreshDir()
	{
		m_dir = Dir(m_dir.path);
	}

	REFLECT_WINDOW(ContentBrowserWindow);
}
#include "content_browser_window.h"

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	void ContentBrowserWindow::init()
	{
		// m_menuItemNames.push_back("Import...");
		// m_menuItemNames.push_back(ContextMenu::Separator);

		std::set<std::string> types = TypeFactory::list("MenuItem");
		for (const std::string& type : types)
		{
			std::unique_ptr<MenuItem> item(TypeFactory::instantiate<MenuItem>(type));
			if (item)
			{
				if (item->getCategory() == "Assets")
				{
					m_menuItemNames.push_back(item->getName());
					m_menuItems.push_back(std::move(item));
				}
			}
		}

		if (!m_menuItems.empty())
		{
			m_menuItemNames.push_back(ContextMenu::Separator);
		}
		m_menuItemNames.push_back("Refresh");
	}

	void ContentBrowserWindow::render()
	{
		processInput(m_selectedItem);

		if (Layout::button(TextIcon::plus()))
		{
			addFolder();
		}

		Layout::sameLine();

		const std::string previousFilter = m_filter;
		Layout::input(TextIcon::search(), m_filter);

		Layout::separator();

		if (m_dir.path != m_root)
		{
			if (Layout::selectable("..", false))
			{
				m_state = NavigationState::Navigating;
				selectFile(m_dir.parent);
			}

			Layout::endDrag("FILE_MOVE", [this, file = m_dir.parent](void* const data, const size_t) -> void
				{
					const std::filesystem::path from = *(const std::filesystem::path*)data;
					moveFile(from, file);
					refreshDirectory();
				}
			);
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
				bool shouldRefresh = false;
				const bool isCurrentFileADirectory = std::filesystem::is_directory(file);
				if (isCurrentFileADirectory && name != "..")
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

				Layout::beginDrag("FILE_MOVE", name, (void*)(&file), sizeof(std::filesystem::path));
				if (isCurrentFileADirectory)
				{
					Layout::endDrag("FILE_MOVE", [this, file, &shouldRefresh](void* const data, const size_t) -> void
						{
							const std::filesystem::path from = *(const std::filesystem::path*)data;
							moveFile(from, file);
							shouldRefresh = true;
						}
					);
				}

				if (shouldRefresh)
				{
					refreshDirectory();
					break;
				}

				if (changeDirectory)
				{
					m_dir = Dir(file);
					State::instance().path = m_dir.path;
					break;
				}
			}
		}

		for (const auto& item : m_menuItems)
		{
			item->render();
		}
		m_contextMenu.render();
		m_openFileDialog.render();
	}

	void ContentBrowserWindow::update(const double)
	{
		if (State::instance().hasPendingContentRefresh())
		{
			refreshDirectory();
		}
	}

	void ContentBrowserWindow::processInput(const std::filesystem::path& file)
	{
		Input& input = Input::instance();
		if (Layout::isWindowHovered())
		{
			if (m_state == NavigationState::Navigating
				&& !m_contextMenu.isOpen()
				&& input.isKeyPressed(KeyCode::MouseRightButton))
			{
				m_state = NavigationState::ContextMenu;
				m_contextMenu.open("Context Menu", m_menuItemNames, [this](const std::string& item)-> void
					{
						handleContextMenuInput(item);
					}
				);
			}
		}
		else
		{
			if ((input.isKeyPressed(KeyCode::MouseLeftButton) || input.isKeyPressed(KeyCode::MouseRightButton))
				&& ((m_state == NavigationState::ContextMenu && m_contextMenu.isOpen()) || m_state == NavigationState::Renaming))
			{
				m_state = NavigationState::Navigating;
				m_contextMenu.close();
			}

		}

		if (!Layout::isWindowFocused() || m_selectedItem.empty())
		{
			return;
		}

		if (m_state == NavigationState::Renaming)
		{
			if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
			{
				m_state = NavigationState::Navigating;
				renameFile(file, m_tempRename);
			}
		}
		else if (m_state == NavigationState::Navigating)
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
				refreshDirectory();
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

			refreshDirectory();
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

				refreshDirectory();
			}
		}
	}

	void editor::ContentBrowserWindow::handleContextMenuInput(const std::string& name)
	{
		if (name == "Import...")
		{
			m_openFileDialog.open("Import file...", {}, [](const std::filesystem::path&) -> void
				{
					// TODO
				}
			);
		}
		else if (name == "Refresh")
		{
			refreshDirectory();
		}
		else
		{
			for (const auto& item : m_menuItems)
			{
				if (item->getName() == name)
				{
					item->execute();
					break;
				}
			}
		}
	}

	void editor::ContentBrowserWindow::importFile(const std::filesystem::path&)
	{
	}

	void ContentBrowserWindow::moveFile(const std::filesystem::path& from, const std::filesystem::path& to)
	{
		static const auto getAssetFilename = [](const std::filesystem::path& filename) -> std::string
		{
			return filename.string().substr(0, filename.string().length() - std::string(Asset::Extension).length());
		};

		static const auto renameAsset = [](const std::filesystem::path& from, const std::filesystem::path& to) -> std::filesystem::path
		{
			std::filesystem::path file = to / from.filename();
			int i = 1;
			while (std::filesystem::exists(file))
			{
				file += (" " + std::to_string(i));
			}
			return file;
		};

		if (std::filesystem::is_directory(to) == false)
		{
			return;
		}

		if (Asset::isAsset(from))
		{
			AssetLibrary& library = AssetLibrary::instance();
			Asset descriptor = Asset::load(from);
			std::shared_ptr<Asset> asset = library.find(descriptor.id);
			if (asset)
			{
				const std::filesystem::path newAssetFilename = renameAsset(from, to);
				if (from != newAssetFilename)
				{
					std::filesystem::rename(from, newAssetFilename);
					std::filesystem::rename(getAssetFilename(from), renameAsset(getAssetFilename(from), to));
					refreshDirectory();

					asset->filename = newAssetFilename;
					library.insert(*asset);
				}
			}
		}
		else
		{
			auto destination = to / from.filename();
			int i = 1;
			while (std::filesystem::exists(destination))
			{
				destination += " " + std::to_string(i);
				++i;
			}
			std::filesystem::rename(from, destination);
			refreshDirectory();
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
			refreshDirectory();
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
					refreshDirectory();

					asset->filename = newAssetFilename;
					library.insert(*asset);
				}
			}
		}
	}

	void ContentBrowserWindow::refreshDirectory()
	{
		m_dir = Dir(m_dir.path);
	}

	REFLECT_WINDOW(ContentBrowserWindow);
}
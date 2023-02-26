#include "content_browser_window.h"

#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/editor/widgets/interaction_layout.h>
#include <awesome/editor/widgets/search_layout.h>
#include <awesome/editor/text_icon.h>

ContentBrowserWindow::ContentBrowserWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
}

char* const ContentBrowserWindow::getTitle() const
{
	return "Content Browser";
}

void ContentBrowserWindow::init()
{
	m_root = AssetLibrary::instance().path();
	m_directory = Directory::scan(m_root, Directory::ScanSettings(Asset::Extension, false));
}

void ContentBrowserWindow::render()
{
	processInput(m_selectedItem);

	if (FormLayout::button(TextIcon::plus().c_str()))
	{
		addFolder();
	}
	FormLayout::sameLine();
	SearchLayout::input(m_filter);

	FormLayout::separator();

	FormLayout::beginChild("Content");
	if (m_directory.path != m_root)
	{
		if (FormLayout::selectable("..", false))
		{
			m_state = NavigationState::Navigating;
			selectFile(m_directory.parent);
		}

		// Layout::endDrag("FILE_MOVE", [this, file = m_directory.parent](void* const data, const size_t) -> void
		// 	{
		// 		const std::filesystem::path from = *(const std::filesystem::path*)data;
		// 		moveFile(from, file);
		// 		refreshDirectory();
		// 	}
		// );
	}

	for (const auto& file : m_directory.files)
	{
		const bool isSelected = m_selectedItem == file;
		if (isSelected && m_state == NavigationState::Renaming)
		{
			// Layout::rename(m_tempRename);
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
				if (FormLayout::selectable((std::string(TextIcon::folder()) + " " + name).c_str(), isSelected, [&changeDirectory]() -> void { changeDirectory = true; }))
				{
					m_state = NavigationState::Navigating;
					m_tempRename = name;
					selectFile(file);
				}
			}
			else if (FormLayout::selectable(decorateFile(name).c_str(), isSelected))
			{
				m_state = NavigationState::Navigating;
				m_tempRename = name;
				selectFile(file);
			}

			// Layout::beginDrag("FILE_MOVE", name, (void*)(&file), sizeof(std::filesystem::path));
			// if (isCurrentFileADirectory)
			// {
			// 	Layout::endDrag("FILE_MOVE", [this, file, &shouldRefresh](void* const data, const size_t) -> void
			// 		{
			// 			const std::filesystem::path from = *(const std::filesystem::path*)data;
			// 	moveFile(from, file);
			// 	shouldRefresh = true;
			// 		}
			// 	);
			// }

			if (shouldRefresh)
			{
				refreshDirectory();
				break;
			}

			if (changeDirectory && m_directory.directory(file))
			{
				m_editorState->select(m_directory.path);
				break;
			}
		}
	}
	FormLayout::endChild();
}

void ContentBrowserWindow::update(const double)
{
	// if (State::instance().hasPendingContentRefresh())
	// {
	// 	refreshDirectory();
	// }
}

void ContentBrowserWindow::processInput(const std::filesystem::path& file)
{
	if (m_selectedItem.empty())
	{
		return;
	}

	if (m_state == NavigationState::Renaming)
	{
		if (InteractionLayout::isKeyPressed(KeyCode::Enter) || InteractionLayout::isKeyPressed(KeyCode::Escape))
		{
			m_state = NavigationState::Navigating;
			renameFile(file, m_tempRename);
		}
	}
	else if (m_state == NavigationState::Navigating)
	{
		if (InteractionLayout::isKeyPressed(KeyCode::F2))
		{
			m_state = NavigationState::Renaming;
		}
		else if (InteractionLayout::isKeyPressed(KeyCode::Delete))
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
		std::filesystem::path path = m_directory.path / (DefaultName + ((i == 0) ? "" : std::string(" ") + std::to_string(i)));
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
			refreshDirectory();
			break;
		}
		++i;
	}
}

std::string ContentBrowserWindow::decorateFile(const std::filesystem::path& file)
{
	if (file.has_extension() == false)
	{
		return file.string();
	}

	// const Asset::Type type = Asset::getTypeByExtension(file.extension().string());
	// switch (type)
	// {
	// case Asset::Type::Image: return TextIcon::image(" " + file.string());
	// case Asset::Type::Prefab: return TextIcon::cube(" " + file.string());
	// case Asset::Type::Scene: return TextIcon::tree(" " + file.string());
	// case Asset::Type::SpriteAnimation: return TextIcon::video(" " + file.string());
	// case Asset::Type::Text: return TextIcon::file(" " + file.string());
	// default: return file.string();
	// }

	return file.string();
}

void ContentBrowserWindow::deleteFile(const std::filesystem::path& path)
{
	if (std::filesystem::is_directory(path))
	{
		std::filesystem::remove(path);
	}
	else
	{
		// AssetFilesystem::erase(path);
	}

	m_editorState->unselectAsset();
	m_selectedItem.clear();

	refreshDirectory();
}

void ContentBrowserWindow::importFile(const std::filesystem::path&)
{
}

void ContentBrowserWindow::moveFile(const std::filesystem::path& from, const std::filesystem::path& to)
{
	if (std::filesystem::is_directory(to) == false)
	{
		return;
	}

	if (std::filesystem::is_directory(from))
	{
		auto destination = to / from.filename();
		int i = 1;
		while (std::filesystem::exists(destination))
		{
			destination += " " + std::to_string(i);
			++i;
		}
		std::filesystem::rename(from, destination);
	}
	else
	{
		// AssetFilesystem::move(from, to);
	}
	refreshDirectory();
}

void ContentBrowserWindow::selectFile(const std::filesystem::path& file)
{
	m_selectedItem = file;
	if (std::filesystem::is_directory(file))
	{
		if (m_directory.parent == file && m_directory.up())
		{
			m_editorState->select(m_directory.path);
		}
	}
	else
	{
		AssetLibrary& library = AssetLibrary::instance();
		const AssetRecord* const record = library.database.find(file);
		if (record != nullptr)
		{
			AssetPtr asset = AssetLibrary::instance().find(record->id);
			if (asset != nullptr)
			{
				m_editorState->select(asset);
			}
			else
			{
				m_editorState->unselectAsset();
			}
		}
		else
		{
			m_editorState->unselectAsset();
		}
	}
}

void ContentBrowserWindow::renameFile(const std::filesystem::path& path, const std::string& name)
{
	if (std::filesystem::is_directory(path))
	{
		std::filesystem::rename(path, path.parent_path() / name);
	}
	else
	{
		// AssetFilesystem::rename(path, name);
	}
	refreshDirectory();
}

void ContentBrowserWindow::refreshDirectory()
{
	m_directory.refresh();
}
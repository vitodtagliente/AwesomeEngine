#include "content_browser_window.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/editor_ui.h>

ContentBrowserWindow::ContentBrowserWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
	s_instance = this;
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
	AssetDatabase& database = AssetLibrary::instance().database;

	if (EditorUI::button(EditorUI::Icon::plus.c_str()))
	{
		addNewFolder("New Folder");
	}

	EditorUI::sameLine();
	if (EditorUI::search(m_filter))
	{
		m_selectedItem.reset();
	}

	EditorUI::separator();

	EditorUI::Child::begin("Content");
	if (m_filter.empty())
	{
		if (m_directory.path != m_root)
		{
			if (EditorUI::selectableDoubleClick("..", false))
			{
				m_state = NavigationState::Navigating;
				m_directory.moveUp();
				m_editorState->path = m_directory.path;
			}

			EditorUI::DragDrop::end("File::Move", [this, to = m_directory.parent](void* const data, const size_t) -> void
				{
					const std::filesystem::path file = *(const std::filesystem::path*)data;
					moveFile(file, to);
					m_directory.refresh();
				}
			);
		}

		for (const auto& file : m_directory.files)
		{
			const bool isSelected = m_selectedItem.has_value() && m_selectedItem.value() == file;
			if (isSelected && m_state == NavigationState::Renaming)
			{
				EditorUI::rename(m_tempRename);
			}
			else
			{
				const std::string name = file.stem().string();
				if (std::filesystem::is_directory(file))
				{
					bool changeFolder = false;
					if (EditorUI::selectable((EditorUI::Icon::folder + " " + name).c_str(), isSelected, [&changeFolder]() -> void
						{
							changeFolder = true;
						}
					))
					{
						m_selectedItem = file;
						m_tempRename = name;
					}

						if (changeFolder)
						{
							m_state = NavigationState::Navigating;
							m_directory.move(file);
							m_editorState->path = m_directory.path;
							m_refresh = true;
							break;
						}

						EditorUI::DragDrop::end("File::Move", [this, to = file](void* const data, const size_t) -> void
							{
								const std::filesystem::path file = *(const std::filesystem::path*)data;
								moveFile(file, to);
								m_refresh = true;
							}
						);
				}
				else if (EditorUI::selectable(decorateFile(name).c_str(), isSelected))
				{
					m_state = NavigationState::Navigating;
					// select the asset
					const AssetRecord* const record = database.find(file);
					if (record != nullptr)
					{
						m_editorState->select(*record);
						m_selectedItem = file;
						m_tempRename = name;
					}
					else
					{
						m_editorState->unselectAsset();
						m_selectedItem.reset();
					}
				}
				EditorUI::DragDrop::begin("File::Move", name.c_str(), (void*)(&file), sizeof(std::filesystem::path));
			}
		}
		if (m_refresh)
		{
			m_directory.refresh();
			m_refresh = false;
		}
	}
	else
	{
		for (const AssetRecord& record : database.records)
		{
			const std::filesystem::path file = record.path.string() + Asset::Extension;
			const std::string name = file.stem().string();

			if (!StringUtil::contains(name, m_filter, StringUtil::CompareMode::IgnoreCase)) continue;

			const bool isSelected = m_selectedItem.has_value() && m_selectedItem.value() == file;
			if (isSelected && m_state == NavigationState::Renaming)
			{
				EditorUI::rename(m_tempRename);
			}
			else if (EditorUI::selectable(decorateFile(name).c_str(), isSelected))
			{
				m_state = NavigationState::Navigating;
				// select the asset
				m_editorState->select(record);
				m_selectedItem = file;
				m_tempRename = name;
			}
		}
	}
	EditorUI::Child::end();
}

void ContentBrowserWindow::update(const double)
{
	if (!hasFocus()) return;

	if (!m_selectedItem.has_value())
	{
		return;
	}

	if (m_state == NavigationState::Renaming)
	{
		if (EditorUI::Input::isKeyPressed(KeyCode::Enter) || EditorUI::Input::isKeyPressed(KeyCode::Escape))
		{
			m_state = NavigationState::Navigating;
			if (!std::filesystem::is_directory(m_selectedItem.value()))
				m_editorState->unselectAsset();
			renameFile(m_selectedItem.value(), m_tempRename);
			m_selectedItem.reset();
			m_directory.refresh();
		}
	}
	else if (m_state == NavigationState::Navigating)
	{
		if (EditorUI::Input::isKeyPressed(KeyCode::F2))
		{
			m_state = NavigationState::Renaming;
		}
		else if (EditorUI::Input::isKeyPressed(KeyCode::Delete))
		{
			if (!std::filesystem::is_directory(m_selectedItem.value()))
				m_editorState->unselectAsset();
			deleteFile(m_selectedItem.value());
			m_selectedItem.reset();
			m_directory.refresh();
		}
	}
}

void ContentBrowserWindow::queue_refresh()
{
	m_refresh = true;
}

void ContentBrowserWindow::addNewFolder(const std::string& name)
{
	int i = 0;
	while (true)
	{
		const std::string folderName = (name.empty() ? "New Folder" : name) + ((i == 0) ? "" : " " + std::to_string(i));
		std::filesystem::path path = m_directory.path / folderName;
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
			m_directory.refresh();
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
		const std::filesystem::path resourcePath = path.parent_path() / path.stem();
		if (!std::filesystem::exists(resourcePath)) return;

		AssetDatabase& database = AssetLibrary::instance().database;
		database.erase(resourcePath);

		std::filesystem::remove(path);
		std::filesystem::remove(resourcePath);
		m_editorState->unselectAsset();
	}
}

void ContentBrowserWindow::moveFile(const std::filesystem::path& from, const std::filesystem::path& to)
{
	if (std::filesystem::is_directory(to) == false)
	{
		return;
	}

	if (std::filesystem::is_directory(from))
	{
		const std::filesystem::path newPath = to / from.filename();
		if (std::filesystem::exists(newPath)) return;

		std::filesystem::rename(from, newPath);
	}
	else
	{
		const std::filesystem::path resourcePath = from.parent_path() / from.stem();
		if (!std::filesystem::exists(resourcePath)) return;

		AssetDatabase& database = AssetLibrary::instance().database;
		database.erase(resourcePath);

		const std::filesystem::path newAssetPath = to / from.filename();
		const std::filesystem::path newResourcePath = to / resourcePath.filename();

		std::filesystem::rename(from, newAssetPath);
		std::filesystem::rename(resourcePath, newResourcePath);
		if (std::filesystem::exists(newAssetPath) || std::filesystem::exists(newResourcePath)) return;

		bool newFilesFound = false;
		AssetImporter::import(newResourcePath, newFilesFound);
	}
}

void ContentBrowserWindow::renameFile(const std::filesystem::path& path, const std::string& name)
{
	if (std::filesystem::is_directory(path))
	{
		const std::filesystem::path newPath = path.parent_path() / name;
		if (std::filesystem::exists(newPath)) return;

		std::filesystem::rename(path, newPath);
	}
	else
	{
		const std::filesystem::path resourcePath = path.parent_path() / path.stem();
		if (!std::filesystem::exists(resourcePath)) return;

		AssetDatabase& database = AssetLibrary::instance().database;
		database.erase(resourcePath);

		const std::filesystem::path newAssetPath = resourcePath.parent_path() / (name + resourcePath.extension().string() + path.extension().string());
		const std::filesystem::path newResourcePath = resourcePath.parent_path() / (name + resourcePath.extension().string());
		if (std::filesystem::exists(newAssetPath) || std::filesystem::exists(newResourcePath)) return;

		std::filesystem::rename(path, newAssetPath);
		std::filesystem::rename(resourcePath, newResourcePath);

		bool newFilesFound = false;
		AssetImporter::import(newResourcePath, newFilesFound);
	}
}
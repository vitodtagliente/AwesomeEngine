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
	EditorUI::search(m_filter);

	EditorUI::separator();

	EditorUI::Child::begin("Content");
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

	bool refresh = false;
	const std::optional<AssetRecord>& selectedAsset = m_editorState->selection.asset;
	for (const auto& file : m_directory.files)
	{
		const bool isSelected = selectedAsset.has_value() && selectedAsset->path == file;
		if (isSelected && m_state == NavigationState::Renaming)
		{
			EditorUI::rename(m_tempRename);
		}
		else
		{
			const std::string name = file.stem().string();
			if (std::filesystem::is_directory(file))
			{
				if (EditorUI::selectableDoubleClick((EditorUI::Icon::folder + " " + name).c_str(), isSelected))
				{
					m_state = NavigationState::Navigating;
					m_directory.move(file);
					m_editorState->path = m_directory.path;
					refresh = true;
					break;
				}

				EditorUI::DragDrop::end("File::Move", [this, to = file, &refresh](void* const data, const size_t) -> void
					{
						const std::filesystem::path file = *(const std::filesystem::path*)data;
						moveFile(file, to);
						refresh = true;
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
					m_tempRename = name;
				}
				else
				{
					m_editorState->unselectAsset();
				}
			}
			EditorUI::DragDrop::begin("File::Move", name.c_str(), (void*)(&file), sizeof(std::filesystem::path));
		}
	}
	EditorUI::Child::end();

	if (refresh)
	{
		m_directory.refresh();
	}
}

void ContentBrowserWindow::update(const double)
{
	/*
	if (m_selectedItem.empty())
	{
		return;
	}

	if (m_state == NavigationState::Renaming)
	{
		if (EditorUI::Input::isKeyPressed(KeyCode::Enter) || EditorUI::Input::isKeyPressed(KeyCode::Escape))
		{
			m_state = NavigationState::Navigating;
			renameFile(m_selectedItem, m_tempRename);
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
			deleteFile(m_selectedItem);
		}
	}
	*/
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
		AssetDatabase& database = AssetLibrary::instance().database;
		database.erase(path);
		std::filesystem::remove(path);
		m_editorState->unselectAsset();
	}
	m_directory.refresh();
}

void ContentBrowserWindow::moveFile(const std::filesystem::path& from, const std::filesystem::path& to)
{
	if (std::filesystem::is_directory(to) == false)
	{
		return;
	}

	if (std::filesystem::is_directory(from))
	{
		std::filesystem::rename(from, to / from.filename());
	}
	else
	{
		const std::filesystem::path resourcePath = from.parent_path() / from.stem();
		if (!std::filesystem::exists(resourcePath)) return;

		AssetDatabase& database = AssetLibrary::instance().database;
		database.erase(resourcePath);

		const std::filesystem::path newAssetPath = to / from.filename();
		std::filesystem::rename(from, newAssetPath);
		const std::filesystem::path newResourcePath = to / resourcePath.filename();
		std::filesystem::rename(resourcePath, newResourcePath);

		bool newFilesFound = false;
		AssetImporter::import(newResourcePath, newFilesFound);
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
		const std::filesystem::path resourcePath = path.parent_path() / path.stem();
		if (!std::filesystem::exists(resourcePath)) return;

		AssetDatabase& database = AssetLibrary::instance().database;
		database.erase(resourcePath);

		const std::filesystem::path newAssetPath = path.parent_path() / name / path.extension();
		std::filesystem::rename(path, newAssetPath);
		const std::filesystem::path newResourcePath = resourcePath.parent_path() / name / resourcePath.filename();
		std::filesystem::rename(resourcePath, newResourcePath);

		bool newFilesFound = false;
		AssetImporter::import(newResourcePath, newFilesFound);
	}
}
#include "content_browser_window.h"

#include <imgui.h>

#include <awesome/application/input.h>
#include <awesome/asset/asset_filesystem.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	void ContentBrowserWindow::render()
	{
		processInput(m_selectedItem);

		ImGui::BeginChild("Header", ImVec2(0.f, 26.f), false, ImGuiWindowFlags_NoDecoration); 
		if (Layout::button(TextIcon::plus()))
		{
			addFolder();
		}

		Layout::sameLine();

		const std::string previousFilter = m_filter;
		Layout::input(TextIcon::search(), m_filter);
		ImGui::EndChild();

		Layout::separator();

		ImGui::BeginChild("Content", ImVec2(0.f, 0.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
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
				else if (Layout::selectable(decorateFile(name), isSelected))
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
		ImGui::EndChild();
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
		if (!hasFocus() || m_selectedItem.empty())
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

	std::string editor::ContentBrowserWindow::decorateFile(const std::filesystem::path& file)
	{
		if (file.has_extension() == false)
		{
			return file.string();
		}

		const Asset::Type type = Asset::getTypeByExtension(file.extension().string());
		switch (type)
		{
		case Asset::Type::Image: return TextIcon::image(" " + file.string());
		case Asset::Type::Prefab: return TextIcon::cube(" " + file.string());
		case Asset::Type::Scene: return TextIcon::tree(" " + file.string());
		case Asset::Type::Sprite: return TextIcon::horse(" " + file.string());
		case Asset::Type::SpriteAnimation: return TextIcon::video(" " + file.string());
		case Asset::Type::Text: return TextIcon::file(" " + file.string());
		default: return file.string();
		}
	}

	void ContentBrowserWindow::deleteFile(const std::filesystem::path& path)
	{
		if (std::filesystem::is_directory(path))
		{
			std::filesystem::remove(path);			
		}
		else
		{
			Asset::Descriptor descriptor = Asset::Descriptor::load(path);
			AssetFilesystem::remove(descriptor);
		}

		State::instance().select();
		m_selectedItem.clear();

		refreshDirectory();
	}

	void editor::ContentBrowserWindow::importFile(const std::filesystem::path&)
	{
	}

	void ContentBrowserWindow::moveFile(const std::filesystem::path& from, const std::filesystem::path& to)
	{
		if (std::filesystem::is_directory(to) == false)
		{
			return;
		}

		if (Asset::isAsset(from))
		{
			Asset::Descriptor descriptor = Asset::Descriptor::load(from);
			AssetFilesystem::move(descriptor, to);
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
		}

		refreshDirectory();
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
		}
		else
		{
			Asset::Descriptor descriptor = Asset::Descriptor::load(file);
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

	void ContentBrowserWindow::renameFile(const std::filesystem::path& path, const std::string& name)
	{
		if (std::filesystem::is_directory(path))
		{
			std::filesystem::rename(path, path.parent_path() / name);
		}
		else
		{
			Asset::Descriptor descriptor = Asset::Descriptor::load(path);
			AssetFilesystem::rename(descriptor, name);
		}
		refreshDirectory();
	}

	void ContentBrowserWindow::refreshDirectory()
	{
		m_dir = Dir(m_dir.path);
	}
}
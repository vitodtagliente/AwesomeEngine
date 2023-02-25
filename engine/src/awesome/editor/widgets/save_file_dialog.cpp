#include "save_file_dialog.h"

#include <imgui.h>

#include <awesome/asset/asset.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/text_icon.h>

#include "form_layout.h"

SaveFileDialog::SaveFileDialog()
	: m_directory()
	, m_extension()
	, m_filename()
	, m_handler()
	, m_open(false)
	, m_root()
	, m_title("Save File Dialog")
{
}

void SaveFileDialog::close()
{
	m_open = false;
}

void SaveFileDialog::open(const std::string& title, const std::string& extension, const std::function<void(const std::filesystem::path&)>& handler)
{
	m_directory = Directory::scan(Editor::instance()->state.path, Directory::ScanSettings(Asset::Extension, false));
	m_extension = extension;
	m_handler = handler;
	m_title = title;
	m_open = true;
}

void SaveFileDialog::render()
{
	if (m_open && !ImGui::IsPopupOpen(m_title.c_str()))
	{
		ImGui::OpenPopup(m_title.c_str());
	}

	ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (m_directory.path != m_root && ImGui::Selectable("..", false, ImGuiSelectableFlags_DontClosePopups))
		{
			m_directory.up();
		}

		for (const auto& file : m_directory.files)
		{
			const std::string filename = file.stem().string();
			bool changeDirectory = false;
			if (std::filesystem::is_directory(file) && filename != "..")
			{
				if (ImGui::Selectable(TextIcon::folder(" " + filename).c_str(), false, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_DontClosePopups))
				{
					if (ImGui::IsMouseDoubleClicked(0))
					{
						changeDirectory = true;
					}
				}
			}
			else if (file.stem().extension() == m_extension)
			{
				if (ImGui::Selectable(filename.c_str(), false, ImGuiSelectableFlags_DontClosePopups))
				{
					m_filename = file.stem().stem().string();
				}
			}

			if (changeDirectory)
			{
				m_directory.directory(file);
				break;
			}
		}

		FormLayout::separator();

		FormLayout::input("Filename", m_filename);
		if (FormLayout::button("Cancel"))
		{
			m_open = false;
			ImGui::CloseCurrentPopup();
		}

		FormLayout::sameLine();

		if (FormLayout::button(TextIcon::save(" Save").c_str()))
		{
			const std::filesystem::path fileToSave = m_directory.path / (StringUtil::endsWith(m_filename, m_extension) ? m_filename : m_filename + m_extension);
			m_handler(fileToSave);
			m_filename.clear();
			ImGui::CloseCurrentPopup();
			m_open = false;
		}
		ImGui::EndPopup();
	}
}
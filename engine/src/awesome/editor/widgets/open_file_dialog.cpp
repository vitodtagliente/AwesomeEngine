#include "open_file_dialog.h"

#include <imgui.h>

#include <awesome/data/asset_library.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	OpenFileDialog::OpenFileDialog()
		: m_dir(State::instance().path)
		, m_extensions()
		, m_handler()
		, m_open(false)
		, m_root(AssetLibrary::instance().getDirectory())
		, m_selectedFile()
		, m_title("Open File Dialog")
	{
	}

	void OpenFileDialog::close()
	{
		m_open = false;
	}

	void OpenFileDialog::open(const std::string& title, const std::vector<std::string>& extensions, const std::function<void(const std::filesystem::path&)>& handler)
	{
		m_dir = Dir(State::instance().path);
		m_extensions = extensions;
		m_handler = handler;
		m_open = true;
		m_selectedFile.reset();
		m_title = title;
	}

	void OpenFileDialog::render()
	{
		if (m_open && !ImGui::IsPopupOpen(m_title.c_str()))
		{
			ImGui::OpenPopup(m_title.c_str());
		}

		ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (m_dir.path != m_root && ImGui::Selectable("..", false, ImGuiSelectableFlags_DontClosePopups))
			{
				m_dir = Dir(m_dir.parent);
			}

			for (const auto& file : m_dir.files)
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
							m_selectedFile.reset();
						}
					}
				}
				else if (m_extensions.empty()
					|| std::find(m_extensions.begin(), m_extensions.end(), file.stem().extension()) != m_extensions.end())
				{
					if (ImGui::Selectable(filename.c_str(), m_selectedFile.has_value() && file == *m_selectedFile, ImGuiSelectableFlags_DontClosePopups))
					{
						m_selectedFile = file;
					}
				}

				if (changeDirectory)
				{
					m_dir = Dir(file);
					break;
				}
			}

			Layout::separator();

			if (Layout::button("Cancel"))
			{
				m_open = false;
				ImGui::CloseCurrentPopup();
			}

			Layout::sameLine();

			if (Layout::button(TextIcon::save(" Open")))
			{
				if (m_selectedFile.has_value() && std::filesystem::exists(*m_selectedFile))
				{
					m_handler(*m_selectedFile);
					State::instance().isContentChanged = true;
					m_open = false;
					m_selectedFile.reset();
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::EndPopup();
		}
	}
}
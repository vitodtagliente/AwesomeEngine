#include "file_dialog.h"

#include <imgui.h>

#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

namespace editor
{
	void FileDialog::open(const std::function<void(const std::filesystem::path&)>& handler)
	{
		m_open = true;
		m_handler = handler;
	}

	void FileDialog::render()
	{
		if (m_open && !ImGui::IsPopupOpen("FileDialog"))
		{
			ImGui::OpenPopup("FileDialog");
		}

		if (ImGui::BeginPopupModal("FileDialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			Layout::input("Filename", m_filename);
			if (Layout::button("Cancel"))
			{
				m_open = false;
				ImGui::CloseCurrentPopup();
			}
			
			Layout::sameLine();

			if (Layout::button("Save"))
			{
				m_handler(State::instance().path / (m_filename + ".scene"));
				m_filename.clear();
				m_open = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

}
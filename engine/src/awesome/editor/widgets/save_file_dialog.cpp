#include "save_file_dialog.h"

#include <imgui.h>

#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

namespace editor
{
	SaveFileDialog::SaveFileDialog(const std::string& extension)
		: m_extension(extension)
		, m_filename()
		, m_handler()
		, m_open()
	{
	}

	void SaveFileDialog::open(const std::function<void(const std::filesystem::path&)>& handler)
	{
		m_open = true;
		m_handler = handler;
	}

	void SaveFileDialog::render(const std::string& name)
	{
		const std::string title = !name.empty() ? name : "Save File Dialog";
		if (m_open && !ImGui::IsPopupOpen(title.c_str()))
		{
			ImGui::OpenPopup(title.c_str());
		}

		ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal(title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
				m_handler(State::instance().path / (StringUtil::endsWith(m_filename, m_extension) ? m_filename : m_filename + m_extension));
				m_filename.clear();
				m_open = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

}
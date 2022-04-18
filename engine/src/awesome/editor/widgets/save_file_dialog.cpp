#include "save_file_dialog.h"

#include <imgui.h>

#include <awesome/core/string_util.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/icons.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

namespace editor
{
	SaveFileDialog::SaveFileDialog(const std::string& extension)
		: m_dir(AssetLibrary::instance().getDirectory())
		, m_extension(extension)
		, m_filename()
		, m_handler()
		, m_open(false)
		, m_root(AssetLibrary::instance().getDirectory())
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
			if (m_dir.path != m_root && Layout::selectable("..", false))
			{
				m_dir = Dir(m_dir.parent);
			}

			for (const auto& file : m_dir.files)
			{
				const std::string filename = file.stem().string();
				bool changeDirectory = false;
				if (std::filesystem::is_directory(file) && filename != "..")
				{
					Layout::selectable(std::string(ICON_FA_FOLDER) + " " + filename, false, [&changeDirectory]() -> void { changeDirectory = true; });
				}
				else
				{
					Layout::selectable(filename, false);
				}

				if (changeDirectory)
				{
					m_dir = Dir(file);
					break;
				}
			}

			Layout::separator();

			Layout::input("Filename", m_filename);
			if (Layout::button("Cancel"))
			{
				m_open = false;
				ImGui::CloseCurrentPopup();
			}

			Layout::sameLine();

			if (Layout::button("Save"))
			{
				m_handler(m_dir.path / (StringUtil::endsWith(m_filename, m_extension) ? m_filename : m_filename + m_extension));
				m_filename.clear();
				m_open = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

}
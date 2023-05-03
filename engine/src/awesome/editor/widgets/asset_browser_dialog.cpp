#include "asset_browser_dialog.h"

#include <imgui.h>

#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/editor_ui.h>

void AssetBrowserDialog::close()
{
	m_open = false;
}

void AssetBrowserDialog::open(const std::string& id, const int type, const std::function<void(const AssetRecord&)>& handler)
{
	if (type != AssetType_Invalid)
	{
		m_handler = handler;
		m_id = id;
		m_open = true;
		m_type = type;
	}
}

void AssetBrowserDialog::render(const std::string& id)
{
	static const float s_widgetWidth = 400.f;

	if (id != m_id) return;

	if (m_open && !ImGui::IsPopupOpen("Asset Browser Dialog"))
	{
		ImGui::OpenPopup("Asset Browser Dialog");
	}

	ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(s_widgetWidth, 0.f));
	if (ImGui::BeginPopupModal("Asset Browser Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		EditorUI::search(m_filter);

		EditorUI::Child::begin("Content", 0.f, 240.f);
		for (const AssetRecord& record : AssetLibrary::instance().database.records)
		{
			if (record.type != m_type) continue;

			const std::string name = record.path.stem().string();
			if (!m_filter.empty() && !StringUtil::contains(name, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				continue;
			}

			const bool isSelected = m_selectedAsset ? m_selectedAsset->id == record.id : false;
			if (ImGui::Selectable(name.c_str(), isSelected, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_DontClosePopups))
			{
				m_selectedAsset = AssetLibrary::instance().database.find(record.id);
				if (ImGui::IsMouseDoubleClicked(0))
				{
					if (m_handler)
					{
						m_handler(*m_selectedAsset);
					}
					m_open = false;
					ImGui::CloseCurrentPopup();
				}
				break;
			}
		}
		EditorUI::Child::end();

		ImGui::BeginChild("BottomBar", ImVec2(0.f, 22.f), false, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);

		if (EditorUI::button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
			m_open = false;
		}

		EditorUI::sameLine();

		if (EditorUI::button((EditorUI::Icon::save + " Select").c_str()))
		{
			if (m_selectedAsset && m_handler)
			{
				m_handler(*m_selectedAsset);
			}
			ImGui::CloseCurrentPopup();
			m_open = false;
		}
		ImGui::EndChild();

		ImGui::EndPopup();
	}
}
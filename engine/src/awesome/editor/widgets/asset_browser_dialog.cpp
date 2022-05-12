#include "asset_browser_dialog.h"

#include <imgui.h>

#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>

namespace editor
{
	AssetBrowserDialog::AssetBrowserDialog()
		: m_filter()
		, m_handler()
		, m_id()
		, m_open()
		, m_selectedAsset()
		, m_type(Asset::Type::None)
	{
	}

	void AssetBrowserDialog::close()
	{
		m_open = false;
	}

	void AssetBrowserDialog::open(const std::string& id, const Asset::Type type, const std::function<void(const AssetPtr&)>& handler)
	{
		m_handler = handler;
		m_id = id;
		m_open = true;
		m_type = type;
	}

	void AssetBrowserDialog::render(const std::string& id)
	{
		if (id != m_id) return;

		if (m_open && !ImGui::IsPopupOpen("Asset Browser Dialog"))
		{
			ImGui::OpenPopup("Asset Browser Dialog");
		}

		ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(400.f, 0.f));
		if (ImGui::BeginPopupModal("Asset Browser Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::BeginChild("Header", ImVec2(0.f, 22.f), false, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
			Layout::input(TextIcon::search(), m_filter);
			ImGui::EndChild();

			ImGui::BeginChild("Content", ImVec2(0.f, 240.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
			const auto descriptors = AssetLibrary::instance().list(m_type);
			for (const Asset::Descriptor& descriptor : descriptors)
			{
				const std::string name = descriptor.path.stem().string();
				if (!m_filter.empty() && !StringUtil::contains(name, m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				const bool isSelected = m_selectedAsset ? m_selectedAsset->descriptor == descriptor : false;
				if (ImGui::Selectable(name.c_str(), isSelected, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_DontClosePopups))
				{
					m_selectedAsset = AssetLibrary::instance().find(descriptor.id);
					if (ImGui::IsMouseDoubleClicked(0))
					{
						if (m_handler)
						{
							m_handler(m_selectedAsset);
						}
						m_open = false;
						ImGui::CloseCurrentPopup();
					}
					break;
				}
			}
			ImGui::EndChild();

			ImGui::BeginChild("BottomBar", ImVec2(0.f, 22.f), false, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);

			if (Layout::button("Cancel"))
			{
				m_open = false;
				ImGui::CloseCurrentPopup();
			}

			Layout::sameLine();

			if (Layout::button(TextIcon::save(" Select")))
			{
				if (m_selectedAsset != nullptr && m_handler)
				{
					m_handler(m_selectedAsset);
				}
				m_open = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndChild();

			ImGui::EndPopup();
		}
	}
}
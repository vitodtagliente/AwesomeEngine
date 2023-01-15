#include "asset_browser_dialog.h"

#include <imgui.h>

#include <awesome/asset/asset_library.h>
#include <awesome/asset/image_asset.h>
#include <awesome/core/string_util.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/editor/layout.h>

void AssetBrowserDialog::close()
{
	m_open = false;
}

void AssetBrowserDialog::open(const std::string& id, const std::string& type, const std::function<void(const AssetPtr&)>& handler)
{
	m_handler = handler;
	m_id = id;
	m_open = true;
	m_type = type;
}

void AssetBrowserDialog::render(const std::string& id)
{
	static const float s_widgetWidth = 400.f;

	if (id != m_id) return;

	if (m_open && !Layout::isPopupOpen("Asset Browser Dialog"))
	{
		ImGui::OpenPopup("Asset Browser Dialog");
	}

	ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(s_widgetWidth, 0.f));
	if (ImGui::BeginPopupModal("Asset Browser Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::BeginChild("Header", ImVec2(0.f, 22.f), false, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
		Layout::input(TextIcon::search(), m_filter);
		Layout::endChild();

		Layout::beginChild("Content", 0.f, 240.f);
		for (const auto& record : AssetLibrary::instance().database.records)
		{
			if (record->type != m_type) continue;

			const std::string name = record->path.stem().string();
			if (!m_filter.empty() && !StringUtil::contains(name, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				continue;
			}

			const bool isSelected = m_selectedAsset ? m_selectedAsset->id == record->id : false;
			if (ImGui::Selectable(name.c_str(), isSelected, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_DontClosePopups))
			{
				m_selectedAsset = AssetLibrary::instance().find(record->id);
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
		Layout::endChild();

		ImageAssetPtr imageAsset = std::dynamic_pointer_cast<ImageAsset>(m_selectedAsset);
		if (imageAsset != nullptr)
		{
			ImGui::BeginChild("Image Preview", ImVec2(0.f, 200.f), false, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
			Layout::image(imageAsset, s_widgetWidth, 200.f);
			ImGui::EndChild();
		}

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
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
		, m_open()
		, m_selectedAsset()
		, m_title("Asset Browser Dialog")
		, m_type(Asset::Type::None)
	{
	}

	void AssetBrowserDialog::close()
	{
		m_open = false;
	}

	void AssetBrowserDialog::open(const Asset::Type type, const std::function<void(const AssetPtr&)>& handler)
	{
		m_handler = handler;
		m_open = true;
		m_type = type;
	}

	void AssetBrowserDialog::render()
	{
		if (m_open && !ImGui::IsPopupOpen(m_title.c_str()))
		{
			ImGui::OpenPopup(m_title.c_str());
		}

		ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(300.0f, 300.0f));
		if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			Layout::input(TextIcon::search(), m_filter);

			const auto descriptors = AssetLibrary::instance().list(m_type);
			for (const Asset::Descriptor& descriptor : descriptors)
			{
				const std::string name = descriptor.path.stem().string();
				if (!m_filter.empty() && !StringUtil::contains(name, m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				if (ImGui::Selectable(name.c_str(), m_selectedAsset ? m_selectedAsset->descriptor == descriptor : false, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_DontClosePopups))
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

			Layout::separator();

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

			ImGui::EndPopup();
		}
	}
}
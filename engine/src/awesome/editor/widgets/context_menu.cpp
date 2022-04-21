#include "context_menu.h"

#include <imgui.h>

namespace editor
{
	void ContextMenu::close()
	{
		m_open = false;
	}

	void ContextMenu::open(const std::string& title, const std::vector<std::string>& items, const std::function<void(const std::string&)>& handler)
	{
		m_handler = handler;
		m_items = items;
		m_open = true;
		m_title = title;
	}

	void ContextMenu::render()
	{
		if (m_open && !ImGui::IsPopupOpen(m_title.c_str()))
		{
			ImGui::OpenPopup(m_title.c_str());
		}

		if (ImGui::BeginPopup(m_title.c_str()))
		{
			for (const auto& item : m_items)
			{
				if (item == Separator)
				{
					ImGui::Separator();
					continue;
				}

				if (ImGui::Selectable(item.c_str(), false))
				{
					m_handler(item);
					m_open = false;
					break;
				}
			}
			ImGui::EndPopup();
		}
	}
}
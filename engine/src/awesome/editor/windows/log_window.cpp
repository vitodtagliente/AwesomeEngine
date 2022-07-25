#include "log_window.h"

#include <sstream>

#include <imgui.h>

#include <awesome/application/application.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	void LogWindow::render()
	{
		ImGui::BeginChild("Header", ImVec2(0.f, 26.f), false, ImGuiWindowFlags_NoDecoration);
		const std::string previousFilter = m_filter;
		Layout::input(TextIcon::search(), m_filter);
		ImGui::EndChild();

		Layout::separator();

		for (const std::string& log : m_logs)
		{
			if (m_filter.empty() || StringUtil::contains(log, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				Layout::text(log);
			}
		}
	}

	void LogWindow::onLog(const std::string& time, const std::string& category, const std::string& level, const std::string& message)
	{
		if (m_logs.size() >= s_maxLogs)
		{
			m_logs.erase(m_logs.begin());
		}

		std::ostringstream s;
		s << time + " [" + category + "][" << level << "] " << message;
		m_logs.push_back(s.str());
	}

	REFLECT_WINDOW(LogWindow)
}
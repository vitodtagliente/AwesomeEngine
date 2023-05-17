#include "log_window.h"

#include <sstream>

#include <awesome/core/string_util.h>
#include <awesome/editor/editor_ui.h>

char* const LogWindow::getTitle() const
{
	return "Console";
}

void LogWindow::render()
{
	EditorUI::search(m_filter);

	for (const std::string& log : m_logs)
	{
		if (m_filter.empty() || StringUtil::contains(log, m_filter, StringUtil::CompareMode::IgnoreCase))
		{
			EditorUI::text(log.c_str());
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
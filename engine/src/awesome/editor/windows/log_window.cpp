#include "log_window.h"

#include <sstream>

#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

std::string LogWindow::getTitle() const
{
	return "Output";
}

void LogWindow::render()
{
	Layout::beginChild("Header", 0.f, 26.f);
	const std::string previousFilter = m_filter;
	Layout::input(TextIcon::search(), m_filter);
	Layout::endChild();

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
#include "logger.h"

Logger::IListener::IListener()
{
	Logger::instance().m_listeners.push_back(this);
}

void Logger::log(const std::string& category, const std::string& level, const std::string& message)
{
	for (IListener* const listener : m_listeners)
	{
		if (listener)
		{
			listener->onLog(category, level, message);
		}
	}
}
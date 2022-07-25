#include "logger.h"

Logger::IListener::IListener()
{
	Logger::instance().m_listeners.push_back(this);
}

Logger::IListener::~IListener()
{
	std::vector<IListener*>& listeners = Logger::instance().m_listeners;
	const auto& it = std::find(listeners.begin(), listeners.end(), this);
	if (it != listeners.end())
	{
		listeners.erase(it);
	}
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
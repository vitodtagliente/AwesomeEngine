#include "logger.h"

#include <chrono>
#include <format>

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
	const time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time_str = std::ctime(&time);
	time_str.resize(time_str.size() - 1);

	for (IListener* const listener : m_listeners)
	{
		if (listener)
		{
			listener->onLog(time_str, category, level, message);
		}
	}
}
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/singleton.h>

class Logger : public Singleton<Logger>
{
public:
	Logger() = default;
	virtual ~Logger() = default;

	class IListener
	{
	public:
		IListener();
		virtual ~IListener();

		virtual void onLog(const std::string& category, const std::string& level, const std::string& message) = 0;
	};
	friend IListener;

	void log(const std::string& category, const std::string& level, const std::string& message);

private:
	std::vector<IListener*> m_listeners;
}; 

#define INFO_LOG(category, message) Logger::instance().log(category, "INFO", message);
#define WARN_LOG(category, message) Logger::instance().log(category, "WARN", message);
#define ERR_LOG(category, message)  Logger::instance().log(category, "ERR", message);
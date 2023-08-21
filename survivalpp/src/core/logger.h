/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "singleton.h"

class Logger : public Singleton<Logger>
{
public:
	class IListener
	{
	public:
		friend class Logger;

		IListener();
		virtual ~IListener();

	protected:
		virtual void onLog(const std::string& time, const std::string& category, const std::string& level, const std::string& message) = 0;
	};
	friend IListener;

	void log(const std::string& category, const std::string& level, const std::string& message);

private:
	std::vector<IListener*> m_listeners;
}; 

#define INFO_LOG(category, message) Logger::instance().log(category, "INFO", message);
#define WARN_LOG(category, message) Logger::instance().log(category, "WARN", message);
#define ERR_LOG(category, message)  Logger::instance().log(category, "ERR", message);

#define THIS_FUNC std::string(__FUNCTION__) + "("  + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"
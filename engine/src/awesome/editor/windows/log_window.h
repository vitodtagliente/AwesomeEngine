/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/logger.h>
#include <awesome/editor/window.h>

class LogWindow : public Logger::IListener, public Window
{
public:
	virtual char* const getTitle() const override;
	virtual void render() override;

private:
	virtual void onLog(const std::string& time, const std::string& category, const std::string& level, const std::string& message) override;

	std::string m_filter;
	std::vector<std::string> m_logs;

	static constexpr size_t s_maxLogs{ 10000 };
};
/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/logger.h>
#include <awesome/editor/window.h>

#include "log_window_generated.h"

CLASS()
class LogWindow : public Logger::IListener, public Window
{
public:
	LogWindow() = default;
	virtual ~LogWindow() = default;

	std::string getTitle() const override { return "Log"; }
	void render() override;

	virtual void onLog(const std::string& time, const std::string& category, const std::string& level, const std::string& message) override;

	GENERATED_BODY()

private:
	std::string m_filter;
	std::vector<std::string> m_logs;

	static constexpr size_t s_maxLogs{ 1000 };
};
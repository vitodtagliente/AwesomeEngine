/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <vdtproto/runtime.h>

#include <awesome/core/logger.h>
#include <awesome/editor/window.h>

namespace editor
{
	class LogWindow : public Window, public Logger::IListener, public IProtoClass
	{
	public:
		LogWindow() = default;
		virtual ~LogWindow() = default;

		std::string getTitle() const override { return "Log"; }
		void render() override;

		virtual void onLog(const std::string& time, const std::string& category, const std::string& level, const std::string& message) override;

		PROTO()

	private:
		std::string m_filter;
		std::vector<std::string> m_logs;

		static constexpr size_t s_maxLogs{ 1000 };
	};
}
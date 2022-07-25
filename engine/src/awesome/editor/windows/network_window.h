/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/logger.h>
#include <awesome/editor/window.h>

namespace editor
{
	class NetworkWindow : public Window, public Logger::IListener
	{
	public:
		NetworkWindow() = default;
		virtual ~NetworkWindow() = default;

		std::string getTitle() const override { return "Network"; }
		void render() override;

		virtual void onLog(const std::string& category, const std::string& level, const std::string& message) override;

		REFLECT()

	private:
		std::vector<std::string> m_logs;

		static constexpr size_t s_maxLogs{ 100 };
	};
}
#include "network_window.h"

#include <sstream>

#include <awesome/application/application.h>
#include <awesome/editor/layout.h>
#include <awesome/net/network_manager.h>

namespace editor
{
	void NetworkWindow::render()
	{
		net::NetworkManager& networkManager = net::NetworkManager::instance();
		switch (networkManager.getType())
		{
		case net::NetworkManager::Type::Unknown:
		{
			const Application::Settings& settings = Application::instance().getSettings();

			if (Layout::button("Start Server"))
			{
				networkManager.startServer(static_cast<uint16_t>(settings.serverPort), static_cast<unsigned int>(settings.maxServerConnections));
			}

			Layout::sameLine();

			if (Layout::button("Connect"))
			{
				networkManager.startClient(settings.serverIp, static_cast<uint16_t>(settings.serverPort));
			}
			break;
		}
		case net::NetworkManager::Type::Server:
		{
			if (Layout::button("Stop Server"))
			{
				
			}
			break;
		}
		case net::NetworkManager::Type::Client:
		{
			if (Layout::button("Stop Client"))
			{

			}
			break;
		}
		}

		Layout::separator();

		for (const std::string& log : m_logs)
		{
			Layout::text(log);
		}
	}

	void NetworkWindow::onLog(const std::string& time, const std::string& category, const std::string& level, const std::string& message)
	{
		if (category != "Net") return;

		if (m_logs.size() >= s_maxLogs)
		{
			m_logs.erase(m_logs.begin());
		}

		std::ostringstream s;
		s << time + " [" << level << "] " << message;
		m_logs.push_back(s.str());
	}

	REFLECT_WINDOW(NetworkWindow)
}
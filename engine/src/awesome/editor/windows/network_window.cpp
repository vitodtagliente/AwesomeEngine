#include "network_window.h"

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
	}

	REFLECT_WINDOW(NetworkWindow)
}
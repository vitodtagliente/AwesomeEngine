#include "network_window.h"

#include <awesome/application/application.h>
#include <awesome/editor/layout.h>
#include <awesome/net/network_manager.h>

std::string NetworkWindow::getTitle() const
{
	return "Network";
}

void NetworkWindow::render()
{
	net::NetworkManager& networkManager = net::NetworkManager::instance();
	switch (networkManager.getState())
	{
	case net::NetworkManager::State::Offline:
	{
		const ApplicationSettings& settings = Application::instance().settings;

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
	case net::NetworkManager::State::Server:
	{
		if (Layout::button("Stop Server"))
		{

		}
		break;
	}
	case net::NetworkManager::State::Client:
	{
		if (Layout::button("Stop Client"))
		{

		}
		break;
	}
	}
}
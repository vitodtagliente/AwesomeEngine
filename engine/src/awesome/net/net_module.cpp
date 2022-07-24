#include "net_module.h"

#include <vdtnet/common.h>

#include <awesome/application/application.h>
#include <awesome/application/input.h>
#include <awesome/net/network_manager.h>

#include "private/commands_loader.h"

#include "client.h"

namespace net
{
	void Module::startup()
	{
		net::startup();
		// load the commands
		CommandsLoader loader;
		loader.load();
	}

	void Module::update(const double deltaTime)
	{
		NetworkManager::instance().update(deltaTime);
		
		if (Input::instance().isKeyPressed(KeyCode::N))
		{
			// auto client = std::make_unique<Client>();
			// client->connect(Application::instance().getSettings().serverIp, static_cast<Address::port_t>(Application::instance().getSettings().serverPort));
			// 
			// Hello request;
			// request.text = "Hello Server";
			// client->call("HelloCommand", request);
		}
	}

	void Module::shutdown()
	{
		net::shutdown();
	}
}
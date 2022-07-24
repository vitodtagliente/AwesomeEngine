#include "net_module.h"

#include <vdtnet/common.h>

#include <awesome/application/application.h>
#include <awesome/application/input.h>
#include <awesome/net/network_manager.h>
#include "server_commands/hello_command.h"

#include "private/commands_loader.h"

#include "client.h"

namespace net
{
	static std::unique_ptr<Client> s_client;

	void Module::startup()
	{
		net::startup();
		// load the commands
		CommandsLoader loader;
		loader.load();


		// test
		TypeFactory::load<HelloCommand>();
	}

	void Module::update(const double deltaTime)
	{
		NetworkManager::instance().update(deltaTime);

		// test
		if (Input::instance().isKeyPressed(KeyCode::N))
		{
			s_client = std::make_unique<Client>();
			s_client->connect(Application::instance().getSettings().serverIp, static_cast<Address::port_t>(Application::instance().getSettings().serverPort));

			Hello request;
			request.text = "Hello Server";
			s_client->call("HelloCommand", request);
		}

		if (s_client)
		{
			s_client->update();
		}
	}

	void Module::shutdown()
	{
		net::shutdown();
	}
}
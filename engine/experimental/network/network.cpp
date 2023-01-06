#include "network.h"

#include <assert.h>

#include <vdtnet/common.h>

#include <awesome/application/application.h>
#include <awesome/application/input.h>
#include <awesome/net/network_manager.h>

#include "client.h"

Network* Network::s_instance{ nullptr };

Network::Network()
	: ApplicationModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void Network::startup()
{
	net::startup();
}

void Network::update(const double deltaTime)
{
	net::NetworkManager::instance().update(deltaTime);

	// test
	// if (Input::instance().isKeyPressed(KeyCode::N))
	// {
	// 	s_client = std::make_unique<Client>();
	// 	s_client->connect(Application::instance().getSettings().serverIp, static_cast<Address::port_t>(Application::instance().getSettings().serverPort));
	// 
	// 	// command::ConnectRequest request;
	// 	// s_client->call<command::ConnectRequest, command::ConnectCommand>(request);
	// }

	// if (s_client)
	// {
	// 	s_client->update();
	// }
}

void Network::shutdown()
{
	net::shutdown();
}
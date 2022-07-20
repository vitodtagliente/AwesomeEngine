#include "net_module.h"

#include <vdtnet/common.h>

#include <awesome/net/network_manager.h>

namespace net
{
	static Socket* s_client;

	void Module::startup()
	{
		net::startup();
	}

	void Module::update(const double deltaTime)
	{
		NetworkManager::instance().update(deltaTime);
		// static bool s_one = false;
		// if (!s_one)
		// {
		// 	int32_t byteSent{ 0 };
		// 	std::string welcome_text = "ciao";
		// 	s_client->sendTo(net::Address("127.0.0.1", 96000), (uint8_t*)welcome_text.c_str(), welcome_text.size(), byteSent);
		// 	s_one = true;
		// }
	}

	void Module::shutdown()
	{
		net::shutdown();
	}
}
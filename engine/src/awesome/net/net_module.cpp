#include "net_module.h"

#include <vdtnet/common.h>

#include <awesome/application/application.h>
#include <awesome/application/input.h>
#include <awesome/net/network_manager.h>

#include "client.h"

namespace net
{
	struct Hello : public ISerializable
	{
		std::string text;

		virtual json::value serialize() const override
		{
			return json::object({
				{"text", text}
				});
		}
		virtual void deserialize(const json::value& value) override
		{
			text = value.safeAt("text").as_string("");
		}
	};

	void Module::startup()
	{
		net::startup();
	}

	void Module::update(const double deltaTime)
	{
		NetworkManager::instance().update(deltaTime);
		
		if (Input::instance().isKeyPressed(KeyCode::N))
		{
			auto client = std::make_unique<Client>();
			client->connect(Application::instance().getSettings().serverIp, Application::instance().getSettings().serverPort);

			Hello request;
			request.text = "Hello Server";
			client->call("hello", request);
		}
	}

	void Module::shutdown()
	{
		net::shutdown();
	}
}
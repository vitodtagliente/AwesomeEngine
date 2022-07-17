#include "net_module.h"

#include <vdtnet/common.h>

namespace net
{
	void Module::startup()
	{
		net::startup();
	}

	void Module::update(const double deltaTime)
	{

	}

	void Module::shutdown()
	{
		net::shutdown();
	}
}
#include "commands_loader.h"

#include <awesome/core/reflection.h>

#include <awesome/net/commands/update_world_command.h>

namespace net
{
	void CommandsLoader::load()
	{
		TypeFactory::load<net::UpdateWorldCommand>();
	}
}
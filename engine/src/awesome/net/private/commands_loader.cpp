#include "commands_loader.h"

#include <awesome/core/reflection.h>

#include <awesome/net/commands/connect_command.h>
#include <awesome/net/commands/disconnect_command.h>
#include <awesome/net/commands/ping_command.h>
#include <awesome/net/commands/update_world_command.h>

namespace net
{
	void CommandsLoader::load()
	{
		TypeFactory::load<command::ConnectCommand>();
		TypeFactory::load<command::DisconnectCommand>();
		TypeFactory::load<command::PingCommand>();
		TypeFactory::load<command::UpdateWorldCommand>();
	}
}
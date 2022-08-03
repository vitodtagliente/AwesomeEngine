#include "commands_loader.h"

#include <awesome/net/commands/connect_command.h>
#include <awesome/net/commands/disconnect_command.h>
#include <awesome/net/commands/ping_command.h>
#include <awesome/net/commands/update_world_command.h>

namespace net
{
	void CommandsLoader::load()
	{
		command::ConnectCommand::autoload();
		command::DisconnectCommand::autoload();
		command::PingCommand::autoload();
		command::UpdateWorldCommand::autoload();
	}
}
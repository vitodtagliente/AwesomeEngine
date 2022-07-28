#include "ping_command.h"

namespace net
{
	namespace command
	{
		json::value PingRequest::serialize() const
		{
			return json::value();
		}

		void PingRequest::deserialize(const json::value&)
		{

		}

		CommandError PingCommand::execute(UserSession* const userSession, const PingRequest&)
		{
			userSession->resetInactivityTime();
			return CommandError::OK;
		}

		REFLECT_SERVER_COMMAND(PingCommand)
	}
}
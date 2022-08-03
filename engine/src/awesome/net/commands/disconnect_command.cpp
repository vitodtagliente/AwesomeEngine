#include "disconnect_command.h"

namespace net
{
	namespace command
	{
		json::value DisconnectRequest::serialize() const
		{
			return json::value();
		}

		void DisconnectRequest::deserialize(const json::value&)
		{

		}

		CommandError DisconnectCommand::execute(UserSession* const userSession, const DisconnectRequest&)
		{
			userSession->disconnect();
			return CommandError::OK;
		}
	}
}
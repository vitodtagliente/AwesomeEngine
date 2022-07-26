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

		void DisconnectCommand::execute(UserSession* const userSession, const DisconnectRequest& request)
		{
			userSession->disconnect();
		}

		REFLECT_SERVER_COMMAND(DisconnectCommand)
	}
}
#include "connect_command.h"

namespace net
{
	namespace command
	{
		json::value ConnectRequest::serialize() const
		{
			return json::value();
		}

		void ConnectRequest::deserialize(const json::value&)
		{

		}

		json::value ConnectResponse::serialize() const
		{
			return json::value();
		}

		void ConnectResponse::deserialize(const json::value&)
		{

		}

		CommandError ConnectCommand::execute(UserSession* const userSession, const ConnectRequest&, ConnectResponse&)
		{
			if (userSession->getState() == UserSession::State::PendingConnection)
			{
				userSession->connect();
			}
			return CommandError::OK;
		}

		REFLECT_SERVER_COMMAND(ConnectCommand)
	}
}
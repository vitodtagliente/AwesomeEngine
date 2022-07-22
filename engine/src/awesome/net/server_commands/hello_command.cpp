/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "hello_command.h"

namespace net
{
	void HelloCommand::execute(UserSession* const userSession, const Hello&)
	{
		userSession->state = UserSession::State::Connected;
	}
	
	REFLECT_SERVER_COMMAND(HelloCommand)
}
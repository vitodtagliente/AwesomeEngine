/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/net/server_command.h>

namespace net
{
	namespace command
	{
		struct PingRequest : public ISerializable
		{
			virtual json::value serialize() const override;
			virtual void deserialize(const json::value& value) override;
		};

		class PingCommand : public ServerCommandNoResponse<PingRequest>
		{
		public:
			PingCommand() = default;
			virtual ~PingCommand() = default;

			virtual void execute(UserSession* const userSession, const PingRequest& request) override;

			REFLECT()
		};
	}
}
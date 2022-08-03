/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/net/server_command.h>

namespace net
{
	namespace command
	{
		struct DisconnectRequest : public ISerializable
		{
			virtual json::value serialize() const override;
			virtual void deserialize(const json::value& value) override;
		};

		class DisconnectCommand : public ServerCommandNoResponse<DisconnectRequest>, public IProtoClass
		{
		public:
			DisconnectCommand() = default;
			virtual ~DisconnectCommand() = default;

			virtual CommandError execute(UserSession* const userSession, const DisconnectRequest& request) override;

			PROTO()
		};
	}
}
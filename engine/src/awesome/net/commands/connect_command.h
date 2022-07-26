/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/net/server_command.h>

namespace net
{
	namespace command
	{
		struct ConnectRequest : public ISerializable
		{
			virtual json::value serialize() const override;
			virtual void deserialize(const json::value& value) override;
		};

		struct ConnectResponse : public ISerializable
		{
			virtual json::value serialize() const override;
			virtual void deserialize(const json::value& value) override;
		};

		class ConnectCommand : public ServerCommand<ConnectRequest, ConnectResponse>
		{
		public:
			ConnectCommand() = default;
			virtual ~ConnectCommand() = default;

			virtual ConnectResponse execute(UserSession* const userSession, const ConnectRequest& request) override;

			REFLECT()
		};
	}
}
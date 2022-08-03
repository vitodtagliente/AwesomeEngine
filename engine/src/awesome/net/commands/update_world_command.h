/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/net/client_command.h>

namespace net
{
	namespace command
	{
		struct UpdateWorldRequest : public ISerializable
		{
			json::value data;

			virtual json::value serialize() const override;
			virtual void deserialize(const json::value& value) override;
		};

		class UpdateWorldCommand : public ClientCommandNoResponse<UpdateWorldRequest>, public IProtoClass
		{
		public:
			UpdateWorldCommand() = default;
			virtual ~UpdateWorldCommand() = default;

			virtual void execute(const UpdateWorldRequest& request) override;

			PROTO()
		};
	}
}
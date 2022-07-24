/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/net/client_command.h>

namespace net
{

	struct UpdateWorldRequest : public ISerializable
	{
		std::string data;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
	};

	class UpdateWorldCommand : public ClientCommandNoResponse<UpdateWorldRequest>
	{
	public:
		UpdateWorldCommand() = default;
		virtual ~UpdateWorldCommand() = default;

		virtual void execute(const UpdateWorldRequest& request) override;

		REFLECT()
	};
}
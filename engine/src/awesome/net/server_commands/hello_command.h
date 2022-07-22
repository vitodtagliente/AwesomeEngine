/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "awesome/net/server_command.h"

namespace net
{
	struct Hello : public ISerializable
	{
		std::string text;

		virtual json::value serialize() const override
		{
			return json::object({
				{"text", text}
				});
		}
		virtual void deserialize(const json::value& value) override
		{
			text = value.safeAt("text").as_string("");
		}
	};

	class HelloCommand : public ServerCommandNoResponse<Hello>
	{
	public:
		HelloCommand() = default;

		virtual void execute(UserSession* const userSession, const Hello& request) override;

		REFLECT()
	};
}
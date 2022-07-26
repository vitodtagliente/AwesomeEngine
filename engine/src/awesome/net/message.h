/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>

#include "net_id.h"

namespace net
{
	enum class CommandPhase;
}

REFLECT_ENUM(net::CommandPhase,
	Request,
	Response
)

namespace net
{
	struct Message : public ISerializable
	{
		struct Header
		{
			netid id;
			double version{ 0.1 };
			std::string commandId;
			CommandPhase commandPhase{ CommandPhase::Request };
			std::map<std::string, std::string> attributes;
		};

		struct Body
		{
			json::value data;
		};

		Header header;
		Body body;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
	};
}